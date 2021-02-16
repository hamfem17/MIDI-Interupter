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

  for(int i = 0; file.available(); i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println((String)file.read());
  }
  file.close();
}

void loop() {


}
