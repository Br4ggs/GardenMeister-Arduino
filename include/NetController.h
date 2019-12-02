#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H

#include "stdlib.h"
#include "arduino_secrets.h"
#include <ArduinoHttpClient.h>
#include <WiFi101.h>

class NetController
{
private:
    WiFiClient wifi;
    //HttpClient http;
    //char serverAddress[] = "xxx.xxx.xxx.xxx";
    //int port = 5000;
    IPAddress ip;
    int status = WL_IDLE_STATUS;
    const char ssid[24] = SECRET_SSID;
    const char pass[11] = SECRET_PASS;
public:
    NetController();
};

#endif