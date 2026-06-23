# Sistema de Irrigação para Estufa
## Objetivo
Controlar a umidade do solo. O sensor de umidade do solo HD-38 monitora a umidade. Se ela cair abaixo de um limite preestabelecido, o sistema aciona um relé que ligaria uma bomba d'água para irrigação (simulada por motor DC). Os dados são visualizados no Grafana. O acionamento do relé deve ser feito via mensagem recebida do MQTT, e não diretamente pelo sketch.

### Gráficos
**Grafana (tipo: dados)**
- Stat: umidade
- Stat: motor DC

### Tópicos MQTT
- **Gravar:**
- rpiot/<grupo99>/patio/esp32/umidade. Exemplo mensagem:
'{"stationId":"EIF001","latitude":-28.47410011,"longitude":-
49.02539825,"type":"SE","umidade":20.5}'
- rpiot/<grupo99>/patio/esp32/irrigacao. Exemplo mensagem:
'{"stationId":"EIF001","latitude":-28.47410011,"longitude":-
49.02539825,"type":"SE","irrigacao": 1}'

- **Ler:**
- rpiot/<grupo99>/patio/esp32/irrigacao. Se 1 aciona relé, se 0 desliga.

### Lista de Componentes
- ESP32 DevKit V1
- Sensor de Umidade do Solo HD-38
- Módulo Relé
- Protoboard e Jumpers
- Motor DC (simula a bomba d'água)

### Esquema de Ligação:
- Sensor DHT -> ESP32:
- VCC -> 3.3V
- GND -> GND
- DATA -> GPIO02
- Módulo Relé -> ESP32:
- VCC -> VIN (5V)
- GND -> GND
- IN -> GPIO04
- Módulo Relé -> Motor DC:
- COM -> 5V
- NC -> VCC (o outro conector do Motor deve ser ligado ao GND)
