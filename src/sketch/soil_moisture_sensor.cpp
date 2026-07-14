#include "soil_moisture_sensor.h"

SoilMoistureSensor::SoilMoistureSensor(int n_pin){
  SoilMoistureSensor::pin = n_pin;
}

void SoilMoistureSensor::initialize(){
  pinMode(SoilMoistureSensor::pin, INPUT);
}

//immersed in pure water the values from 400 to 1500 (max)
//when is completely dry the max value is 4095
//com a terra meio molhada fica entorno de 2500 - 3500
//com a terra molhada fica entorno de 1250 - 1600
//com a terra extremamente molhada fica entorno de 1000 - 1200
//com a terra extremamente seca: 4095
//com a terra em estado natural após seca: 4095
int SoilMoistureSensor::checkHumidity(){
    return analogRead(SoilMoistureSensor::pin);
}
