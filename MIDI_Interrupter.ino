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

  if(!SD.exists("test.midi") {
    Serial.println("Datei \"test.midi\" nicht vorhanden");
  }
  
  file = SD.open("test.midi", FILE_READ);

  Serial.println("File erstellet");
  for(int i = 0; i < 20; i++) {
    Serial.println("i: ");
    Serial.print((String)file.read());
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
