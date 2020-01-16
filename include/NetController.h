/**
 * Initial author: Emiel van den Brink
 **/

#ifndef NETCONTROLLER_H
#define NETCONTROLLER_H

#include "stdlib.h"
#include "arduino_secrets.h"
#include <ArduinoHttpClient.h>
#include <WiFi101.h>
//Controller class responsible for communicating with the server via HTTP over Wifi.
//wifi SSID, Password, Server address and server port are stored in a separate arduino_secrets.h file.
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
    String responseBody;
    int responseCode;
public:
    NetController();
    //Send a Get request to the server to the given path.
    //Note: This method might take a couple seconds to complete.
    int Get(const char *path);
    //Send a post request to the server containing postData to the given path.
    //Note: This method might take a couple of seconds to complete.
    int Post(const char *path, const char *postData, const char *contentType);
    //Get the Arduino's IP address given to it by the router, as an IPAddress object.
    IPAddress GetIPAddress();
    //Get the Arduino's IP address given to it by the router, as a String.
    String GetIPAddressStr();
    //Get the response body returned from the last request.
    String GetResponseBody();
    //Get the response code returned from the last request.
    int GetResponseCode();
};

#endif