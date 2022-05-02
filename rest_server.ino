#include <SPI.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <Dhcp.h>
#include <Ethernet.h>
#include "restapi.h"
#include "ArduinoJson.h"

//Network configuration for arduino
byte mac[] = {0x33, 0xAA, 0xDE, 0xAD, 0xC0, 0xD4}; 
byte ip[] = {192, 168, 0, 160};
byte gateway[] = { 192, 168, 0, 1 };
byte subnet[] = { 255, 255, 0, 0 };
restServer *myServer;

//Json config
StaticJsonDocument<300> doc;

//Pin Config
const int controlPin[44] = {2,3,4,5,6,7,8,9,10,11,12,13,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53}; // define pins


void callbackFunction(EthernetClient *client, char *args){
    Serial.println("GET called!!");
    client->println("{\"callback\":1}");
}

void postFunction(EthernetClient *client, char *args){
    Serial.println("Post called!!!!!!");
    Serial.println(args);
    client->println(args);
    DeserializationError error = deserializeJson(doc, args);
    if (error) {
      Serial.print("Error deserialize json:");
      Serial.println(error.c_str());
      return 1;
    }

    if(strcmp(doc["value"], "HIGH") == 0){
      digitalWrite(doc["pin"],HIGH);  
    }else if(strcmp(doc["value"], "LOW") == 0){
      digitalWrite(doc["pin"],LOW);
    }
    

    
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  myServer = new restServer(mac, ip, gateway, subnet,80);
  myServer->addRoute("/index.php", GET, &callbackFunction);
  myServer->addRoute("/setButton", POST, &postFunction);
  Serial.println("Starting API");
  for(int i=0; i<44; i++)
  {
    pinMode(controlPin[i], OUTPUT);// set pin as output
    digitalWrite(controlPin[i], HIGH); // set initial state OFF for low trigger relay

  }
}

void loop() {
  myServer->serve();
}
