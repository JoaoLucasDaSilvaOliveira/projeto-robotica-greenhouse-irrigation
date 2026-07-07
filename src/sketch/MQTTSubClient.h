#ifndef MQTT_SUB_CLI_H
#define MQTT_SUB_CLI_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Definição da assinatura da função que vai lidar com as mensagens
typedef void (*MqttMessageHandler)(String message);

class MQTTSubClient {
  private:
    WiFiClient wifiClient;
    PubSubClient mqtt;

    String mqttHostName;
    int mqttPort;
    String clientID;
    String mqttUsername;
    String mqttPassword;

    static MQTTSubClient* instance;

  public:
    String ultimaMensagem;

    MQTTSubClient(
      String mqttHostName,
      int mqttPort,
      String clientID,
      String mqttUsername,
      String mqttPassword
    );

    void initialize();
    void startConnection();
    bool checkState();
    void registrarTopicosMQTT();
    void publicarTopicoMQTT(String topic, String message);
    void loop();
    MqttMessageHandler onMessageReceived = nullptr; // Ponteiro para a função

    static void mqttCallback(
      char* topic,
      byte* payload,
      unsigned int length
    );
};

#endif