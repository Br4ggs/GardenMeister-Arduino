#include "NetController.h"

//TODO: wifi password required toggle bool
NetController::NetController()
    :http(wifi, serverAddress, port)
{
    DEBUG_LOGLN("Initializing Netcontroller");
#ifndef NET_DEBUG
    while (status != WL_CONNECTED)
    {
        DEBUG_LOGLN("Attempting connect to network");
        status = WiFi.begin(ssid, pass);
    }

    ip = WiFi.localIP();
#else
    DEBUG_LOGLN("RUNNING IN NETLESS DEBUG MODE");
    ip = IPAddress(0,0,0,0);
#endif
    DEBUG_LOGLN("Connected, ip is:");
    DEBUG_LOGLN(ip);
}

int NetController::Get(const char *path)
{
    DEBUG_LOGLN("Starting get request");
#ifndef NET_DEBUG
    http.get(path);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    responseCode = statusCode;
    responseBody = response;

    http.stop();
#else
    DEBUG_LOGLN("NET_DEBUG is enabled, no get request has been made");
    int statusCode = -1;
    responseCode = -1;
    responseBody = "{}";
#endif
    return statusCode;
}

int NetController::Post(const char *path, const char *postData, const char *contentType)
{
    DEBUG_LOGLN("Starting post request");
#ifndef NET_DEBUG
    http.post(path, contentType, postData);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    responseCode = statusCode;
    responseBody = response;

    http.stop();
#else
    DEBUG_LOGLN("NET_DEBUG is enabled, no post request has been made");
    int statusCode = -1;
    responseCode = -1;
    responseBody = "{}";
#endif
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

String NetController::GetResponseBody()
{
    return responseBody;
}

int NetController::GetResponseCode()
{
    return responseCode;
}