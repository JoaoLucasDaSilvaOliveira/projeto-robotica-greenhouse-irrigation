# Sistema de Irrigação para Estufa

Projeto final da disciplina de Robótica: sistema de monitoramento e acionamento de irrigação para uma estufa, usando ESP32, sensor de umidade do solo, MQTT e visualização no Grafana.

## Objetivo

Controlar a umidade do solo de forma automatizada. O ESP32 lê o sensor de umidade do solo, publica a leitura via MQTT e solicita o acionamento da irrigação quando o solo está seco. O relé não é acionado diretamente pela regra local: o sketch publica a solicitação em MQTT e liga ou desliga o relé apenas quando recebe a mensagem de comando no tópico de irrigação.

## Funcionamento

1. O sensor de umidade do solo é lido pelo ESP32.
2. A leitura é publicada no tópico MQTT de umidade.
3. Quando a leitura passa do limite configurado para solo seco, o ESP32 publica uma solicitação de irrigação.
4. O ESP32 também assina o tópico de irrigação.
5. Ao receber `{"irrigacao": 1}`, o relé é ligado.
6. Ao receber `{"irrigacao": 0}`, o relé é desligado.
7. Os dados publicados podem ser consumidos por uma stack de monitoramento e exibidos no Grafana.

## Hardware

- ESP32 DevKit V1
- Sensor de umidade do solo HD-38
- Módulo relé
- Protoboard
- Jumpers
- Motor DC ou LED para simular a bomba d'água

## Ligações

### Sensor de umidade do solo -> ESP32

| Sensor | ESP32 |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| AO/DATA | GPIO34 |

### Módulo relé -> ESP32

| Relé | ESP32 |
| --- | --- |
| VCC | VIN/5V |
| GND | GND |
| IN | GPIO04 |

### Relé -> carga simulada

| Relé | Carga |
| --- | --- |
| COM | 5V |
| NC | VCC da carga |
| GND da carga | GND |

## Tópicos MQTT

Os tópicos definidos no sketch usam o grupo `grupo05`.

### Publicação de umidade

Tópico:

```text
rpiot/grupo05/patio/esp32/umidade
```

Exemplo de mensagem:

```json
{
  "stationId": "EIF001",
  "latitude": -28.47410011,
  "longitude": -49.02539825,
  "type": "SE",
  "umidade": 20.5
}
```

### Publicação e leitura da irrigação

Tópico:

```text
rpiot/grupo05/patio/esp32/irrigacao
```

Exemplo para ligar:

```json
{
  "stationId": "EIF001",
  "latitude": -28.47410011,
  "longitude": -49.02539825,
  "type": "SE",
  "irrigacao": 1
}
```

Exemplo para desligar:

```json
{
  "stationId": "EIF001",
  "latitude": -28.47410011,
  "longitude": -49.02539825,
  "type": "SE",
  "irrigacao": 0
}
```

## Visualização

No Grafana, criar painéis do tipo `Stat` para acompanhar:

- Umidade do solo
- Estado da irrigação ou motor DC

## Estrutura do projeto

```text
.
|-- README.md
|-- documentation/
|   `-- RELATÓRIO_GREENHOUSE_IRRIGATION.pdf
|-- infra/
|   |-- docker-compose.yml
|   `-- enabled_plugins
`-- src/
    |-- diagram.json
    `-- sketch/
        |-- sketch.ino
        |-- topic.h
        |-- relay.*
        |-- soil_moisture_sensor.*
        |-- MQTTSubClient.*
        |-- WifiLib.*
        |-- config.example.h
        `-- libraries.txt
```

## Configuração

1. Copie `src/sketch/config.example.h` para `src/sketch/config.h`.
2. Preencha as credenciais de Wi-Fi.
3. Preencha host, porta, usuário, senha e client ID do broker MQTT.
4. Abra o projeto no Arduino IDE, PlatformIO ou Wokwi.
5. Instale a biblioteca `ArduinoJson`.
6. Compile e envie o sketch para o ESP32.

## Referência

Este README foi atualizado com base no relatório final do projeto:

> RELATÓRIO: GREENHOUSE IRRIGATION. Grupo 05, ADS 5º Semestre. Disponível em: [documentation/RELATÓRIO_GREENHOUSE_IRRIGATION.pdf](documentation/RELAT%C3%93RIO_GREENHOUSE_IRRIGATION.pdf).

---

# Greenhouse Irrigation System

Final project for the Robotics course: a greenhouse irrigation monitoring and control system using ESP32, a soil moisture sensor, MQTT, and Grafana visualization.

## Goal

Control soil moisture automatically. The ESP32 reads the soil moisture sensor, publishes the reading through MQTT, and requests irrigation when the soil is dry. The relay is not activated directly by the local rule: the sketch publishes an MQTT request and only turns the relay on or off when it receives a command message on the irrigation topic.

## How It Works

1. The ESP32 reads the soil moisture sensor.
2. The reading is published to the MQTT humidity topic.
3. When the reading exceeds the configured dry-soil threshold, the ESP32 publishes an irrigation request.
4. The ESP32 also subscribes to the irrigation topic.
5. When it receives `{"irrigacao": 1}`, the relay is turned on.
6. When it receives `{"irrigacao": 0}`, the relay is turned off.
7. The published data can be consumed by a monitoring stack and displayed in Grafana.

## Hardware

- ESP32 DevKit V1
- HD-38 soil moisture sensor
- Relay module
- Breadboard
- Jumper wires
- DC motor or LED to simulate the water pump

## Wiring

### Soil moisture sensor -> ESP32

| Sensor | ESP32 |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| AO/DATA | GPIO34 |

### Relay module -> ESP32

| Relay | ESP32 |
| --- | --- |
| VCC | VIN/5V |
| GND | GND |
| IN | GPIO04 |

### Relay -> simulated load

| Relay | Load |
| --- | --- |
| COM | 5V |
| NC | Load VCC |
| Load GND | GND |

## MQTT Topics

The topics defined in the sketch use the `grupo05` group.

### Humidity publishing

Topic:

```text
rpiot/grupo05/patio/esp32/umidade
```

Message example:

```json
{
  "stationId": "EIF001",
  "latitude": -28.47410011,
  "longitude": -49.02539825,
  "type": "SE",
  "umidade": 20.5
}
```

### Irrigation publishing and subscription

Topic:

```text
rpiot/grupo05/patio/esp32/irrigacao
```

Example to turn irrigation on:

```json
{
  "stationId": "EIF001",
  "latitude": -28.47410011,
  "longitude": -49.02539825,
  "type": "SE",
  "irrigacao": 1
}
```

Example to turn irrigation off:

```json
{
  "stationId": "EIF001",
  "latitude": -28.47410011,
  "longitude": -49.02539825,
  "type": "SE",
  "irrigacao": 0
}
```

## Visualization

In Grafana, create `Stat` panels to monitor:

- Soil moisture
- Irrigation or DC motor state

## Project Structure

```text
.
|-- README.md
|-- documentation/
|   `-- RELATÓRIO_GREENHOUSE_IRRIGATION.pdf
|-- infra/
|   |-- docker-compose.yml
|   `-- enabled_plugins
`-- src/
    |-- diagram.json
    `-- sketch/
        |-- sketch.ino
        |-- topic.h
        |-- relay.*
        |-- soil_moisture_sensor.*
        |-- MQTTSubClient.*
        |-- WifiLib.*
        |-- config.example.h
        `-- libraries.txt
```

## Configuration

1. Copy `src/sketch/config.example.h` to `src/sketch/config.h`.
2. Fill in the Wi-Fi credentials.
3. Fill in the MQTT broker host, port, username, password, and client ID.
4. Open the project in Arduino IDE, PlatformIO, or Wokwi.
5. Install the `ArduinoJson` library.
6. Compile and upload the sketch to the ESP32.

## Reference

This README was updated based on the final project report:

> RELATÓRIO: GREENHOUSE IRRIGATION. Group 05, ADS 5th Semester. Available at: [documentation/RELATÓRIO_GREENHOUSE_IRRIGATION.pdf](documentation/RELAT%C3%93RIO_GREENHOUSE_IRRIGATION.pdf).
