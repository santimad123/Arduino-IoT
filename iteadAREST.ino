#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>
#include <DHT.h>


#define DHTTYPE DHT11 
#define DHTPIN 14 //
#define LISTEN_PORT 80 // port to listen in server
#define GPIO 15 // read data from sensor

const char* ssid = "IoT";
const char* pw = "seronoser";

char* serverName = "broker.mqtt-dashboard.com";

float humidity, temperature;
int counter;

WiFiClient espClient;
PubSubClient client(espClient);
WiFiServer server(LISTEN_PORT);

aREST rest = aREST(client, serverName);

DHT dht(DHTPIN, DHTTYPE, GPIO);

int ledControl(String command);
void getDataFromSensor();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  
  Serial.begin(115200);

  //dht.begin();

  rest.set_id("uva2");
  rest.set_name("Sonoff-Itead");

  client.setCallback(callback);
  client.setServer(serverName, 1883);

/*  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);  */            

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pw); // conect to wifi.

  Serial.println("Conecting to wifi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wifi conected");
  
  server.begin(); // server listening to incoming message in port 80

  Serial.println();
  Serial.println(WiFi.localIP());

  char* out_topic = rest.get_topic();

  Serial.println(out_topic);

  counter = millis();

  while(!client.connected()) {

      Serial.println("Connecting to server MQTT protocol..");
      
      if(client.connect("testTopic")){
          Serial.println("Connected to Server");
      }

      else {
        Serial.println("Cant Connect to server, client state: ");
        Serial.print(client.state());
        Serial.println();
      }

      delay(5000);
  }
}

void loop() {

  /*getDataFromSensor(); 

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(); 

  if( (millis() - counter) > 60000) {
    Serial.println(true);
    if (client.connect(servername, port)) {
      Serial.println(true);
      rest.publish(client, "Temperature", temperature);
      rest.publish(client, "Humidity", humidity);
    }
    counter = millis();
  }

  WiFiClient secondClient = server.available();
  if(!secondClient) {
    return;
  }
  while(!secondClient.available()){
    delay(1);
  }
  rest.handle(secondClient);*/

  
  
}

void getDataFromSensor() {
  
  do {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
  }
  
  while(humidity > 900.0 || temperature > 900.0);
    

  delay(60000);
}

void callback(char* topic, byte* payload, unsigned int length){

  rest.handle_callback(client, topic, payload, length);
  }

