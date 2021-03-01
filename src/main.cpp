#include <SD.h>
#include <SPI.h>

File file;

int readBytes(const int length) {
    if(length > sizeof(int)) {
		return -1;
	}
	int value = 0;
    for(int i = 0; i < length; i++) {
		value += (file.read() << (length - i - 1));
    }
	return value;
}

void setup() {

  Serial.begin(9600);
  Serial.println("Initializing SD card");

  if(!SD.begin(10)) { //PD4
      Serial.println("[Error]: Could not initialize SD card!");
      return;
  }
  
  Serial.println("Successfully initialized SD card");

  if(!SD.exists("ACDC_TNT.MID")) {
    Serial.println("File \"ACDC_TNT.MID\" not found");
  }
  
  file = SD.open("ACDC_TNT.MID");
    
  if(readBytes(4) != 1297377380) { //Check header string
    Serial.println("[Error]: Invalid header string");
  }
  else {
    Serial.println("Header string correct");
  }
  
  if(readBytes(4) != 6) { //Check header length
    Serial.println("[Error]: Invalid header lenght!");
  }
  else {
    Serial.println("Header lenght correct");
  }

  switch(readBytes(2)) { //Check file format
    case 0: 
		Serial.println("Single track file format not supported yet ");
		break; 
    case 1:
		Serial.println("Format correct!");
		break;
    case 2:
		Serial.println("Multiple song file format not suported yet!");
		break;
	default:
		Serial.println("[Error]: Invalid file format!");
  }
  
  Serial.print("Number of track chunks that follow the header chunk: "); //Read number of track chunks
  Serial.println(readBytes(2));
  
  for(int i = 9; i < 100; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(file.read(),HEX);
  }
  file.close();
}

void loop() {


}
