#include <SD.h>
#include <SPI.h>

File file;

void setup() {

  Serial.begin(9600);
  Serial.println("Initialisirung der SD-Card....");

  if(!SD.begin(10)) { //D4
      Serial.println("Initialisirung der SD-Card ist fehlgeschlagen");
      return;
  }
  
  Serial.println("Initialisirung der SD-Card ist erfolgreich");

  if(!SD.exists("ACDC_TNT.MID")) {
    Serial.println("Datei \"ACDC_TNT.MID\" nicht vorhanden");
  }
  
  file = SD.open("ACDC_TNT.MID");
  
  uint8_t buf[4];
  
  for(int i = 0; i < 4; i++)
  {
    buf[3 - i] = file.read();
    //Serial.println(buf[3 - i],HEX);//header
  }
  
  if(*((unsigned long int *) buf) != 1297377380)
  {
    Serial.println("Header invalid");
  }
  else
  {
    Serial.println("Header correct");
  }
  
  for(int i = 0; i < 4; i++)
  {
    buf[3 - i] = file.read(); 
    //Serial.println(buf[3 - i],HEX);//header lenght
  }
  
  if(*((unsigned long int *) buf) != 6)
  {
    Serial.println("Header lenght invalid");
  }
  else
  {
    Serial.println("Header lenght correct");
  }

  for(int i = 0; i < 2; i++)
  {
    buf[1 - i] = file.read(); 
    //Serial.println(buf[1 - i],HEX);// Format
  }

  switch(*((unsigned long int *) buf))
  {
    case 0: Serial.println("Single track file format not supported yet "); break; 
    case 1: Serial.println("Format correct!"); break;
    case 2: Serial.println("Multiple song file format not suported yet!"); break;
  }
  
  for(int i = 0; i < 2; i++)
  {
    buf[1 - i] = file.read(); 
    Serial.println(buf[1 - i],HEX);//number of track chunks that follow the header chunk 
  }
  
  
  for(int i = 9; i < 100; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(file.read(),HEX);
  }
  file.close();
}

void loop() {


}
