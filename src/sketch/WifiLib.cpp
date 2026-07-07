#include <string>
#include <WiFi.h>

#include "WifiLib.h"

WifiLib::WifiLib(String ssid, String password){
  this->ssid = ssid;
  this->password = password;
}

void WifiLib::initialize(){
  WiFi.mode(WIFI_STA);
}

void WifiLib::startConnection(){
  WiFi.begin(
    this->ssid,
    this-> password
  );
}

bool WifiLib::checkConnection(){
  return WiFi.status() == WL_CONNECTED;
}