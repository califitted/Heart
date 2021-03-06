







#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "Switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "config.h"


// prototypes
boolean connectWifi();

//on/off callbacks
void heartsOn();
void heartsOff();
void sickOn();
void sickOff();
void lightThreeOn();
void lightThreeOff();
void lightFourOn();
void lightFourOff();
void outletOneOn();
void outletOneOff();
void outletTwoOn();
void outletTwoOff();
void outletThreeOn();
void outletThreeOff();
void outletFourOn();
void outletFourOff();

// Change this before you flash
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *hearts = NULL;
Switch *sick = NULL;
Switch *lightThree = NULL;
Switch *lightFour = NULL;
Switch *outletOne = NULL;
Switch *outletTwo = NULL;
Switch *outletThree = NULL;
Switch *outletFour = NULL;

//relay pin setup for funct
int relayOne = 5;
int relayTwo = 4;
int relayThree = 0;
int relayFour = 2;
int relayFive = 14;
int relaySix = 12;
int relaySeven = 13;
int relayEight = 15;


void setup()
{

 Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();

    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    hearts = new Switch("hearts", 80, heartsOn, heartsOff);
    sick = new Switch("sick", 81, sickOn, sickOff);
    lightThree = new Switch("light Three", 82, lightFourOn, lightFourOff);
    lightFour = new Switch("Light Four", 83, lightFourOn, lightFourOff);
    outletOne = new Switch("Outlet One", 84,outletOneOn, outletOneOff);
    outletTwo = new Switch("Outlet Two", 85, outletTwoOn, outletTwoOff);
    outletThree = new Switch("Outlet Three", 86, outletThreeOn, outletThreeOff);
    outletFour = new Switch("Outlet Four", 87,outletFourOn, outletFourOff);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*hearts);
    upnpBroadcastResponder.addDevice(*sick);
    upnpBroadcastResponder.addDevice(*lightFour);
    upnpBroadcastResponder.addDevice(*lightFour);
    upnpBroadcastResponder.addDevice(*outletOne);
    upnpBroadcastResponder.addDevice(*outletTwo);
    upnpBroadcastResponder.addDevice(*outletThree);
    upnpBroadcastResponder.addDevice(*outletFour);

    //relay pins setup i Used D1,D2,D3,D4,D5,D6,D7,D8 followed as assigned below, if you are willing to change Pin or planning to use extra please Check Image in Github File..:)
    pinMode (5, OUTPUT);
    pinMode (4, OUTPUT);
    pinMode (0, OUTPUT);
    pinMode (2, OUTPUT);
    pinMode (14, OUTPUT);
    pinMode (12, OUTPUT);
    pinMode (13, OUTPUT);
    pinMode (15, OUTPUT);
    digitalWrite (5,HIGH);
    digitalWrite (4,HIGH);
    digitalWrite (0,HIGH);
    digitalWrite (2,HIGH);
    digitalWrite (14,HIGH);
    digitalWrite (12,HIGH);
    digitalWrite (13,HIGH);
    digitalWrite (15,HIGH);
  }
}

void loop()
{
   if(wifiConnected){
      upnpBroadcastResponder.serverLoop();

      hearts->serverLoop();
      sick->serverLoop();
      lightFour->serverLoop();
      lightFour->serverLoop();
      outletOne->serverLoop();
      outletTwo->serverLoop();
      outletThree->serverLoop();
      outletFour->serverLoop();
   }
}

void heartsOff() {
    Serial.print("Switch 1 turn off ...");
    digitalWrite(relayOne, HIGH);   // sets relayOne off
}

void heartsOn() {
    Serial.print("Switch 1 turn on ...");
    digitalWrite(relayOne, LOW);   // sets relayOne on
}

void sickOff() {
    Serial.print("Switch 2 turn off ...");
    digitalWrite(relayTwo, HIGH);   // sets relayOne off
}

void sickOn() {
  Serial.print("Switch 2 turn on ...");
  digitalWrite(relayTwo, LOW);   // sets relayOne on
}

void lightThreeOff() {
    Serial.print("Switch 3 turn off ...");
    digitalWrite(relayThree, LOW);   // sets relayOne on
}

void lightThreeOn() {
  Serial.print("Switch 3 turn on ...");
  digitalWrite(relayThree, HIGH);   // sets relayOne on
}

void lightFourOff() {
    Serial.print("Switch4 turn off ...");
    digitalWrite(relayFour, LOW);   // sets relayOne on
}

void lightFourOn() {
  Serial.print("Switch 4 turn on ...");
  digitalWrite(relayFour, HIGH);   // sets relayOne on
}

//sockets

void outletOneOff() {
    Serial.print("Socket 1 turn off ...");
    digitalWrite(relayFive, LOW);   // sets relayOne on
}

void outletOneOn() {
    Serial.print("Socket 1turn on ...");
    digitalWrite(relayFive, HIGH);   // sets relayOne off
}

void outletTwoOff() {
    Serial.print("Socket 2 turn off ...");
    digitalWrite(relaySix, LOW);   // sets relayOne on
}

void outletTwoOn() {
  Serial.print("Socket 2 turn on ...");
  digitalWrite(relaySix, HIGH);   // sets relayOne on
}

void outletThreeOff() {
    Serial.print("Socket 3 turn off ...");
    digitalWrite(relaySeven, LOW);   // sets relayOne on
}

void outletThreeOn() {
    Serial.print("Socket 3 turn on ...");
    digitalWrite(relaySeven, HIGH);   // sets relayOne off
}

void outletFourOff() {
    Serial.print("Socket  4 turn off ...");
    digitalWrite(relayEight, LOW);   // sets relayOne on
}

void outletFourOn() {
  Serial.print("Socket 4 turn on ...");
  digitalWrite(relayEight, HIGH);   // sets relayOne on
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }

  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}
