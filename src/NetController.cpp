#include "NetController.h"

//TODO: wifi password required toggle bool
NetController::NetController()
    :http(wifi, serverAddress, port)
{
    DEBUG_LOG("Initializing Netcontroller");

    while (status != WL_CONNECTED)
    {
        DEBUG_LOG("Attempting connect to network");
        status = WiFi.begin(ssid, pass);
    }

    ip = WiFi.localIP();
    DEBUG_LOG("Connected, ip is:");
    DEBUG_LOG(ip);
    //todo: add delay(?)
}

String NetController::Get(const char *path)
{
    DEBUG_LOG("Starting get request");
    http.get(path);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    DEBUG_LOG("Get request ended with status code:");
    DEBUG_LOG(statusCode);

    http.stop();
    //TODO: add delay(?)
    return response;
}