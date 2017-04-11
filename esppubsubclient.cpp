// Trying sleepMode for esp82666
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqttClient(client);

const char* ssid =  "IoT";
const char* pass = "seronoser";

void setup() {
  
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin();

  Serial.print("ESP8266 is on for 2 minutes");
  
  for(int i = 0; i < 10; i++){
    Serial.print(".");
      delay(12000);
  }
  
  
}

void loop() {

  delay(500);

  mqttClient.setServer(maker.ifttt.com/trigger/{event}/with/key/euO1c7Uin6eInRYsOt_4tAWhSDjXqQAiev342K0HN3S)

  Serial.println();
  
   // Sleep
  Serial.println("ESP8266 in sleep mode");
  sleep();
}

 void sleep() {

    ESP.deepSleep(20 * 1000000, WAKE_RF_DEFAULT);
 }
