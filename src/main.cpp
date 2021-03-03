#include <SD.h>
#include <SPI.h>
#define PIN 10

File file;

void initSD()
{
  Serial.println("Initializing SD card");

  if(!SD.begin(PIN))
  { //PD4
      Serial.println("[Error]: Could not initialize SD card!");
      return;
  }
  
  Serial.println("Successfully initialized SD card");

  if(!SD.exists("ACDC_TNT.MID"))
  {
    Serial.println("File \"ACDC_TNT.MID\" not found");
  }
  
  file = SD.open("ACDC_TNT.MID");
}

long int readBytes(const int length)
{
    if(length > sizeof(long int)) {
		return -1;
	}

	unsigned long int value = 0;
    for(int i = 0; i < length; i++) {

		value += ((unsigned long)file.read() << 8 * (length - i - 1));
    
    }

	return value;
}

void checkHeader(unsigned int *trackChunks, unsigned int *division)
{
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
  *trackChunks = readBytes(2);
  Serial.println(*trackChunks);

  *division = readBytes(2);
  if(*division >= 0x8000) { //Check division
    Serial.println("SMPTE compatible units not supported yet");
  }
  else {
    Serial.print("Speed = ");
    Serial.print(*division);
    Serial.println(" bpm");
  }
}

void setup() {

  unsigned int trackChunks;
  unsigned int division;

  Serial.begin(9600);
  
  initSD();

  checkHeader(&trackChunks, &division);

  for(int i = 15; i < 100; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(file.read(),BIN);
  }
  file.close();
}

void loop() {


}
