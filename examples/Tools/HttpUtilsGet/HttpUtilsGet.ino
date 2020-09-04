/*
  This sketch Shows how to use the HTTP command to
  makes http request and stores the result in the 
  Sara u201 internal storage
  Circuit:
  - MKRNB 1500 board
*/

#include <ArduinoMqttClient.h>
#include <MKRNB.h>
#include "arduino_secrets.h"


const char PINNUMBER[]     = SECRET_PINNUMBER;
// APN data
const char NB_APN[]      = SECRET_APN;
const char NB_USERNAME[]    = SECRET_USERNAME;
const char NB_PASSWORD[] = SECRET_PASSWORD;

// initialize the library instance
NBHttpUtils httpClient;
GPRS gprs;
NB nbAccess(true);

NBFileUtils fileUtils(false);

// URL, path and port (for example: example.org)
char server[] = "www.arduino.cc";
char path[] = "/asciilogo.txt";
int port = 80; // port 80 is the default for HTTP

// An existing file
constexpr char* filename { "get.ffs" };

// Read bloack size
constexpr unsigned int blockSize { 512 };


const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  bool connected = false;
  // Start the modem with NB.begin()
  // attach the shield to the GPRS network with the APN, login and password
  while (!connected) {
    if ((nbAccess.begin(PINNUMBER, "lpwa.pelion", "streamip", "streamip", false, true) == NB_READY) &&
        (gprs.attachGPRS() == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  // configurae all the parameters to make the http request
  httpClient.configServer(server, port);
  httpClient.get(path, filename);
  delay(5000);
  httpClient.read(filename);
}

void loop() {
  if (httpClient.responseStatus()) {
    Serial.println("received");
    fileUtils.begin(false);
    String fileList[10];
    auto size = fileUtils.listFiles(fileList);
    for (int i = 0; i < size && i <10; i++) {
      if (fileList[i] == filename) {
        Serial.print("file found: ");
        Serial.println(fileList[i]);
      }
    }
    while (1);
  }
}
