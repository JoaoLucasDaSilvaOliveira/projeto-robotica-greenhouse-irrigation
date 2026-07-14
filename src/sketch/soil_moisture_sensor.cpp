#include "soil_moisture_sensor.h"

SoilMoistureSensor::SoilMoistureSensor(int n_pin){
  SoilMoistureSensor::pin = n_pin;
}

void SoilMoistureSensor::initialize(){
  pinMode(SoilMoistureSensor::pin, INPUT);
}

//immersed in pure water the values from 400 to 1500 (max)
//when is completely dry the max value is 4095
//when soil is half wet stay in range of 2500 - 3500
//when soil is wet stay in range of 1250 - 1600
//when soil is extremely wet stay in range of 1000 - 1200
//when soil is extremely dry is 4095
//when soil was dried in air/sun is 4095
int SoilMoistureSensor::checkHumidity(){
    return analogRead(SoilMoistureSensor::pin);
}
