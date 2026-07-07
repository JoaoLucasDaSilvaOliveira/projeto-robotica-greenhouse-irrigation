#ifndef SOIL_MOISTURE_SENSOR
#define SOIL_MOISTURE_SENSOR

#include <Arduino.h>

class SoilMoistureSensor {
  private:
    int pin;

  public:
    SoilMoistureSensor(int n_pin);
    void initialize();
    int checkHumidity();
};

#endif