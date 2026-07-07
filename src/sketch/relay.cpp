#include "relay.h"

Relay::Relay(int n_pin) {
  this->pin = n_pin;
}

void Relay::initialize() {
  pinMode(this->pin, OUTPUT);
  this->turnOff();  
}

void Relay::turnOn() {
  digitalWrite(this->pin, HIGH);
}

void Relay::turnOff() {
  digitalWrite(this->pin, LOW);
}
