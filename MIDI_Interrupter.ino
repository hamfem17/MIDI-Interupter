#include <SD.h>
#include <SPI.h>

File file;

void setup() {

  Serial.begin(9600);
  Serial.println("Initialisirung der SD-Card....");

  if(SD.begin(10) == 0)                                //D4
  {
      Serial.println("Initialisirung der SD-Card ist fehlgeschlagen");
      return;
  }
  Serial.println("Initialisirung der SD-Card ist ervolgreich");

  Serial.println("Erstelle File......");

  file = SD.open("Midi-Datei.txt", FILE_WRITE);
  file.close();

  Serial.println("File erstellet");
}

void loop() {
  // put your main code here, to run repeatedly:

}
