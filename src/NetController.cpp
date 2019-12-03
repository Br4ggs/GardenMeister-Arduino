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
    return response;
}

String NetController::Post(const char *path, const char *postData, const char *contentType)
{
    DEBUG_LOG("Starting post request");
    http.post(path, contentType, postData);

    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    DEBUG_LOG("Post request ended with status code:");
    DEBUG_LOG(statusCode);

    http.stop();
    return response;
}