/*
  This sketch Shows how to use the HTTP command to
  makes http request to the https end point and stores
  the result in the Sara u201 internal storage
  Circuit:
  - MKRNB 1500 board
*/

#include <ArduinoMqttClient.h>
#include <MKRNB.h>
#include "arduino_secrets.h"


const char PINNUMBER[]     = SECRET_PINNUMBER;
// APN data
const char APN[]           = SECRET_APN;
const char USERNAME[]      = SECRET_USERNAME;
const char PASSWORD[]      = SECRET_PASSWORD;


// initialize the library instance
NBHttpUtils httpClient;
NB nbAccess(true);
GPRS gprs;

NBFileUtils fileUtils(false);

// URL, path and port (for example: example.org)
char server[] = "www.google.com"; //"107-systems.org"; //google.com
char path[] = "/"; //"/ota/wifi1010-https-local.ota";
int port = 443; // port 80 is the default for HTTP

// An existing file
constexpr char* filename { "get.bin" };


// Read bloack size
constexpr unsigned int blockSize { 512 };


const long interval = 1000;
unsigned long previousMillis = 0;

int count = 0;

void readFile();

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  bool connected = false;
  // Start the modem with NB.begin()
  while (!connected) {
    if ((nbAccess.begin(PINNUMBER, APN, USERNAME, PASSWORD, false, true) == NB_READY) &&
        (gprs.attachGPRS() == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  fileUtils.begin(false);
  
  httpClient.eraseAllCertificates();
  httpClient.setUserRoots(NB_ROOT_CERTS, NB_NUM_ROOT_CERTS);
  httpClient.setRootCertificate();
  httpClient.setTrustedRoot("Let_s_Encrypt_Authority_X3");
  
  httpClient.enableSSL();
  httpClient.configServer(server, port);
  /*
  delay(5000);
  int size = fileUtils.listFile(filename);
  httpClient.deleteFile(filename);
  */
  delay(5000);
  httpClient.get(path, filename);
  unsigned long start_time=millis();
  while((millis()-start_time)<15000) {
    httpClient.responseStatus();
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
  }
  delay(15000);
  httpClient.read(filename);


}

void loop() {
  if (httpClient.responseStatus()) {
    Serial.println("URC received");

    httpClient.read(filename);
    while (1);
  }
}

void readFile() {
  String fileList[10];
  auto size = fileUtils.listFiles(fileList);
  for (int i = 0; i < size && i <10; i++) {
    if (fileList[i] == filename) {
      Serial.print("file found: ");
      Serial.println(fileList[i]);
    }

  }
}
