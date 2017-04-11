#include <GDBStub.h>
#include <TheThingsNetwork.h>
#include <ESP8266WiFi.h>


// OTAA or ABP keys

#define loraSerial Serial1
#define debugSerial Serial

#define freqPlan TTN_FP_US915 // It also might be TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup() {

    loraSerial.begin(57600);
    debugSerial.begin(9600);

    // OTAA or ABP activation
}

void loop() {

    // Send and recieve messages

  debugSerial.println("Device Information");
  debugSerial.println();
  ttn.showStatus();
  debugSerial.println();
  debugSerial.println("Use the EUI to register the device for OTAA");
  debugSerial.println("-------------------------------------------");
  debugSerial.println();

delay(10000);
}

