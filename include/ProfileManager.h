#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "stdlib.h"
#include "NetController.h"
#include "ArduinoJson.h"

//Management class that knows specific optimal sensor values for plant.
//Can synchronise with server via NetController in order to stay up-to-date
class ProfileManager
{
private:
    float minGrndMoisture = 20.0f;
    float maxGrndMoisture = 50.0f;
    float margin = 5.0f;
    NetController *netController;
public:
    ProfileManager(NetController *net);
    //Register the regulator on the server
    int RegisterRegulator();
    //Retrieve the latest profile from the server
    int SyncProfile();
    //Check if ground moisture level is below minimum desired threshold
    bool GrndMoistureBelowMin(float grndMoisture);
    //Check if ground moisture level is above maximum desired threshold
    bool GrndMoistureAboveMax(float grndMoisture);
    float GetMinGrndMoisture();
    float GetMaxGrndMoisture();
};

#endif