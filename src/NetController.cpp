#include "NetController.h"

//TODO: wifi password required toggle bool
NetController::NetController()
    :http(wifi, serverAddress, port)
{
    DEBUG_LOGLN("Initializing Netcontroller");

    while (status != WL_CONNECTED)
    {
        DEBUG_LOGLN("Attempting connect to network");
        status = WiFi.begin(ssid, pass);
    }

    ip = WiFi.localIP();
    DEBUG_LOGLN("Connected, ip is:");
    DEBUG_LOGLN(ip);
}

String NetController::Get(const char *path)
{
    DEBUG_LOGLN("Starting get request");
    http.get(path);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    DEBUG_LOGLN("Get request ended with status code:");
    DEBUG_LOGLN(statusCode);

    http.stop();
    return response;
}

String NetController::Post(const char *path, const char *postData, const char *contentType)
{
    DEBUG_LOGLN("Starting post request");
    http.post(path, contentType, postData);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    DEBUG_LOGLN("Post request ended with status code:");
    DEBUG_LOGLN(statusCode);

    http.stop();
    return response;
}

IPAddress NetController::GetIPAddress()
{
    return ip;
}