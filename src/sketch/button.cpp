#include "button.h"

Button::Button(int n_pin){
  Button::pin = n_pin;
}

void Button::initialize(){
  pinMode(Button::pin, INPUT);
  Button::state = LOW;
}

bool Button::checkState(){
  Button::state = digitalRead(Button::pin);
  return Button::state;
}
