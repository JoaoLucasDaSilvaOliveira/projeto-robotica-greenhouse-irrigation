#ifndef BUTTON_H
#define BUTTON_H

class Button {
  private:
    int pin;
    int state;

  public:
    Button(int n_pin);
    void initialize();
    bool checkState();
};

#endif