#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <Arduino_JSON.h>
#include "webpage.h"


ESP8266WiFiMulti wifiMulti;

const char* ssid = "Your wifi ssid";
const char* password = "Your wifi password";

AsyncWebServer server(80);
// Create a WebSocket object
AsyncWebSocket ws("/ws");
JSONVar readings;

int ldr_pin = A0;  //ldr is connected to A0
int trigpin = 12;
int ecopin = 14;

String wsdata;

int getdistance(){
  long duration;
  int distance;
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(ecopin, HIGH);
  distance= duration * 0.034 / 2;
  return distance;
}

String getSensorReadings(){
 readings["distance"] = String(getdistance());
 readings["light"] = String(analogRead(ldr_pin));
 String jsonString = JSON.stringify(readings);
 Serial.println(jsonString);
 return jsonString;
}


void init_wifi(){
    delay(10);
    wifiMulti.addAP(ssid, password);
    Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void notifyClients(String state) {
 ws.textAll(state);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
 AwsFrameInfo *info = (AwsFrameInfo*)arg;
 if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
 data[len] = 0;
 wsdata = (char*)data;
 if(wsdata == "give_packet"){
  notifyClients(getSensorReadings());
 }
 }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,AwsEventType type, void *arg, uint8_t *data, size_t len) {
 switch (type) {
 case WS_EVT_CONNECT:
 Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
 break;
 case WS_EVT_DISCONNECT:
 Serial.printf("WebSocket client #%u disconnected\n", client->id());
 break;
 case WS_EVT_DATA:
 handleWebSocketMessage(arg, data, len);
 break;
 case WS_EVT_PONG:
 case WS_EVT_ERROR:
 break;
 }
}

void initWebSocket() {
 ws.onEvent(onEvent);
 server.addHandler(&ws);
}


void setup() {
  Serial.begin(115200);
  pinMode(ldr_pin,INPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(ecopin,INPUT);
  init_wifi();
  initWebSocket();

 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send_P(200, "text/html", index_html);
  });
  // Start server
  server.begin();
}

void loop() {
 ws.cleanupClients();
 delay(3000);
}
