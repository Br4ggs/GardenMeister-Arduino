#include "NetController.h"

//todo wifi password required toggle bool
NetController::NetController()
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