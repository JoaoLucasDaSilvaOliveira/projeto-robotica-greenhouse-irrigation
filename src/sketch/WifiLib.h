#include <Arduino.h>
#ifndef WIFILIB_H
#define WIFILIB_H

class WifiLib {
  private: 
    String ssid;
    String password;

  public: 
    WifiLib(String ssid, String password);
    void initialize();
    void startConnection();
    bool checkConnection();
};

#endif