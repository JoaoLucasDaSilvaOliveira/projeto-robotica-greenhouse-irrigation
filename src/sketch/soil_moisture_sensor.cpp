#include "soil_moisture_sensor.h"

SoilMoistureSensor::SoilMoistureSensor(int n_pin){
  SoilMoistureSensor::pin = n_pin;
}

void SoilMoistureSensor::initialize(){
  pinMode(SoilMoistureSensor::pin, INPUT);
}

//immersed in pure water the values from 400 to 1500 (max)
//when is completely dry the max value is 4095
int SoilMoistureSensor::checkHumidity(){
    return analogRead(SoilMoistureSensor::pin);
}
