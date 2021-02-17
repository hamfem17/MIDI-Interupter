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
    Serial.println(buf[3 - i]);//header
  }
  
  if(*((unsigned long int *) buf) != 1297377380)
  {
    Serial.println("Falsch");
  }
  else
  {
    Serial.println("Richtig");
  }
  
  for(int i = 0; i < 4; i++)
  {
    buf[3 - i] = file.read(); 
    Serial.println(buf[3 - i]);//header lenght
  }
  
  if(*((unsigned long int *) buf) != 6)
  {
    Serial.println("Falsch");
  }
  else
  {
    Serial.println("Richtig");
  }
  
  for(int i = 5; file.available(); i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println((String)file.read());
  }
  file.close();
}

void loop() {


}
