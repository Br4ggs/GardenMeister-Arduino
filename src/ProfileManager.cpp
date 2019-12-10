#include "ProfileManager.h"

ProfileManager::ProfileManager(NetController *net)
{
    netController = net;
}

int ProfileManager::SyncProfile()
{
    String path = "/api/ipprofiles/" + netController->GetIPAddressStr();
    DEBUG_LOGLN(path);
    int rspCode = netController->Get(path.c_str());
    if(rspCode == 200)
    {
        String rspBody = netController->GetResponseBody();
        DEBUG_LOGLN(rspBody);
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, rspBody);

        minGrndMoisture = doc["minSoilMoisture"];
        maxGrndMoisture = doc["maxSoilMoisture"];
    }
    return (rspCode == 200) ? 1 : -1;
}

bool ProfileManager::GrndMoistureBelowThreshold(float grndMoisture)
{
    return grndMoisture <= minGrndMoisture;
}

bool ProfileManager::GrndMoistureWithinRange(float grndMoisture)
{
    return grndMoisture >= (maxGrndMoisture - margin);
}

float ProfileManager::GetMinGrndMoisture()
{
    return minGrndMoisture;
}

float ProfileManager::GetMaxGrndMoisture()
{
    return maxGrndMoisture;
}