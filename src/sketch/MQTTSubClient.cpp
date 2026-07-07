#include "MQTTSubClient.h"
#include "topic.h"

MQTTSubClient* MQTTSubClient::instance = nullptr;

MQTTSubClient::MQTTSubClient(
  String mqttHostName,
  int mqttPort,
  String clientID,
  String mqttUsername,
  String mqttPassword
) : mqtt(wifiClient) {

  this->mqttHostName = mqttHostName;
  this->mqttPort = mqttPort;
  this->clientID = clientID;
  this->mqttUsername = mqttUsername;
  this->mqttPassword = mqttPassword;

  instance = this;
}

void MQTTSubClient::initialize() {

  this->mqtt.setServer(
    this->mqttHostName.c_str(),
    this->mqttPort
  );

  this->mqtt.setCallback(MQTTSubClient::mqttCallback);
}

void MQTTSubClient::mqttCallback(char* topic, byte* payload, unsigned int length) {
  if (instance == nullptr) {
    return;
  }

  String mensagem = "";
  for (unsigned int i = 0; i < length; i++) {
    mensagem += (char) payload[i];
  }

  // Se houver uma função registrada pelo .ino, repassa os dados para lá
  if (instance->onMessageReceived != nullptr) {
    instance->onMessageReceived(mensagem);
  }
}

void MQTTSubClient::startConnection(){
  this->mqtt.connect(
    this->clientID.c_str(),
    this->mqttUsername.c_str(),
    this->mqttPassword.c_str()
  );
}

bool MQTTSubClient::checkState(){
  return this->mqtt.connected();
}

void MQTTSubClient::registrarTopicosMQTT(){
  this->mqtt.subscribe(READ_IRRIGATION_TOPIC);
}

void MQTTSubClient::publicarTopicoMQTT(String topic, String message){
  this->mqtt.publish(topic.c_str(), message.c_str());
}

void MQTTSubClient::loop(){
  this->mqtt.loop();
}