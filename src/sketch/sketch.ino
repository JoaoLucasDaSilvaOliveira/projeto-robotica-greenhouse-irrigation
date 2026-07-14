//arduino libs
#include <Arduino.h>
#include <ArduinoJson.h>

//project libs
#include "config.h"
#include "topic.h"
#include "WifiLib.h"
#include "MQTTSubClient.h"
#include "relay.h"
#include "soil_moisture_sensor.h"

//pin definitions
#define SOIL_HUMIDITY_SENSOR_PIN 34
#define RELAY_PIN 4

//control variables
int humidityLevel;
bool irrigationOn = false;
#define MOCK_LATITUDE -28.47410011
#define MOCK_LONGITUDE -49.02539825 
#define MOCK_STATION_ID "EIF001"


//class instances
WifiLib wifi(WIFI_DNS, WIFI_PASS);
MQTTSubClient mqttClient(MQTT_HOST_IP, MQTT_PORT, MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
Relay relay (RELAY_PIN);
SoilMoistureSensor soilMoistureSensor(SOIL_HUMIDITY_SENSOR_PIN);

//connects to WiFi
void conectarWiFi() {
  wifi.startConnection();
  Serial.print("Conectando WiFi");
  
  while (!wifi.checkConnection()) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi conectado");
}

//connects to MQTT broker
void conectarMQTT() {
  Serial.print("Conectando MQTT");
  
  while (!mqttClient.checkState()) {
    mqttClient.startConnection();
    Serial.print(".");
    delay(100);
  }
  
  Serial.println("\nMQTT conectado");
  mqttClient.registrarTopicosMQTT();
}

//turns irrigation relay on
void turnOnIrrigation () {
  Serial.println("--- Ligando a irrigação! ---");
  relay.turnOn();
}

//turns irrigation relay off
void turnOffIrrigation () {
  Serial.println("--- Desligando a irrigação! ---");
  relay.turnOff();
}

//publishes current humidity level
void monitorHumidityLevel() {
  humidityLevel = soilMoistureSensor.checkHumidity();
  Serial.println("--- Publicando o nível de humidade! ---");
  Serial.print("Nível atual: ");
  Serial.println(humidityLevel);
  JsonDocument doc;                                                              
  doc["stationId"] = MOCK_STATION_ID;
  doc["latitude"] = MOCK_LATITUDE;
  doc["longitude"] = MOCK_LONGITUDE;
  doc["type"] = "SE";
  doc["umidade"] = humidityLevel;
  String output;
  serializeJson(doc, output);
  mqttClient.publicarTopicoMQTT(WRITE_HUMIDITY_TOPIC, output);
  Serial.println("--- Nível publicado! ---");
}

//publishes irrigation start request
void requestStartIrrigation() {
  Serial.println("--- Pedindo para ligar a irrigação! ---");
  JsonDocument doc;   
  doc["stationId"] = MOCK_STATION_ID;
  doc["latitude"] = MOCK_LATITUDE;
  doc["longitude"] = MOCK_LONGITUDE;
  doc["type"] = "SE";
  doc["irrigacao"] = 1;
  String output;
  serializeJson(doc, output);
  mqttClient.publicarTopicoMQTT(WRITE_IRRIGATION_TOPIC, output);
  Serial.println("--- Pedido publicado! ---");
}

//publishes irrigation stop request
void requestStopIrrigation() {
  Serial.println("--- Pedindo para desligar a irrigação! ---");
  JsonDocument doc; 
  doc["stationId"] = MOCK_STATION_ID;
  doc["latitude"] = MOCK_LATITUDE;
  doc["longitude"] = MOCK_LONGITUDE;
  doc["type"] = "SE";
  doc["irrigacao"] = 0;
  String output;
  serializeJson(doc, output);
  mqttClient.publicarTopicoMQTT(WRITE_IRRIGATION_TOPIC, output);
  Serial.println("--- Pedido publicado! ---");
}

//handles irrigation MQTT messages
void monitorIrrigation(String message) {
  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("Erro ao desserializar JSON: ");
    Serial.println(error.c_str());
    return;
  }

  int state = doc["irrigacao"];

  if (state == 1) {
    irrigationOn = true;
    turnOnIrrigation();
  } else {
    irrigationOn = false;
    turnOffIrrigation();
  }
}

void setup() {
  //serial setup
  Serial.begin(115200);
  delay(500);
  
  Serial.println("================================");
  Serial.println("  INICIANDO CONTROLE DE ESTUFA");
  Serial.println("================================\n");

  //component setup
  relay.initialize();
  soilMoistureSensor.initialize();

  //default resolution for ESP32: 12 bits: (0-4095)
  analogReadResolution(12);

  //connection setup
  wifi.initialize();
  conectarWiFi();

  mqttClient.initialize();
  mqttClient.onMessageReceived = monitorIrrigation;
  conectarMQTT();

  Serial.println("Sistema configurado e pronto para inicialização");
  Serial.println("Clique no botão para abaixar o nível de humidade da estufa.");
  Serial.println("Ao chegar no nível mínimo o sistema irá se autoregular.");

}

void loop() {
  //keeps connections alive
  if (!wifi.checkConnection()) {
    Serial.println("WiFi desconectado");
    conectarWiFi();
  }

  if (!mqttClient.checkState()) {
    Serial.println("MQTT desconectado");
    conectarMQTT();
  }
  mqttClient.loop();

  monitorHumidityLevel();

if (humidityLevel > SOIL_WET_S && !irrigationOn) {
  requestStartIrrigation();
} 

if (humidityLevel <= SOIL_WET_S && irrigationOn) {
  requestStopIrrigation();
}
  delay(1000);
}
