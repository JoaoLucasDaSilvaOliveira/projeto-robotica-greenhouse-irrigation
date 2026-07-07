#ifndef RELAY_H
#define RELAY_H

class Relay {
  private:
    int pin;

  public:
    Relay(int n_pin);
    void initialize();
    void turnOn();
    void turnOff();
};

#endif