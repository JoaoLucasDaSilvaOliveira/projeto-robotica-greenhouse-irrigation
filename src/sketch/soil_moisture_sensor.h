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

//THIS MACROS WERE DEFINED BY A FIELD STUDY USING A CONSIDERABLE AMOUNT OF SAND (CONSTRUCTION GRAVEL)
//immersed in pure water the values from 400 to 1500 (max)
#define    1500

#endif