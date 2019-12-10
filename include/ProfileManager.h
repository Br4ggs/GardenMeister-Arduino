#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "stdlib.h"
#include "NetController.h"
#include "ArduinoJson.h"

class ProfileManager
{
private:
    //TODO: placeholder values, change these later
    float minGrndMoisture = 20.0f;
    float maxGrndMoisture = 50.0f;
    float margin = 5.0f;
    NetController *netController;
public:
    ProfileManager(NetController *net);
    int SyncProfile();
    bool GrndMoistureBelowThreshold(float grndMoisture);
    bool GrndMoistureWithinRange(float grndMoisture);
    float GetMinGrndMoisture();
    float GetMaxGrndMoisture();
};

#endif