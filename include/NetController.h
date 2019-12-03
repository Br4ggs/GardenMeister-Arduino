#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H

#include "stdlib.h"
#include "arduino_secrets.h"
#include <ArduinoHttpClient.h>
#include <WiFi101.h>

enum DHT11data
{
    Json = "application/json"
};

class NetController
{
private:
    const int port = SERVER_PORT;
    const char serverAddress[15] = SERVER_ADDRESS;
    const char ssid[24] = SECRET_SSID;
    const char pass[11] = SECRET_PASS;
    WiFiClient wifi;
    HttpClient http;
    IPAddress ip;
    int status = WL_IDLE_STATUS;
public:
    NetController();
    //return types on these?
    String Get(const char *path);
    void Post(const char *path, const char *postData, const char *contentType);
};

#endif