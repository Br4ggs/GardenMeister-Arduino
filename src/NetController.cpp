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

int NetController::Get(const char *path)
{
    DEBUG_LOGLN("Starting get request");
    http.get(path);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    DEBUG_LOGLN("Get request ended with status code:");
    DEBUG_LOGLN(statusCode);

    responseCode = statusCode;
    responseBody = response;

    http.stop();
    return statusCode;
}

int NetController::Post(const char *path, const char *postData, const char *contentType)
{
    DEBUG_LOGLN("Starting post request");
    http.post(path, contentType, postData);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    DEBUG_LOGLN("Post request ended with status code:");
    DEBUG_LOGLN(statusCode);

    responseCode = statusCode;
    responseBody = response;

    http.stop();
    return statusCode;
}

IPAddress NetController::GetIPAddress()
{
    return ip;
}

String NetController::GetIPAddressStr()
{
    return String(ip[0]) + "." + ip[1] + "." + ip[2] + "." + ip[3];
}