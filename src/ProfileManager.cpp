#include "ProfileManager.h"

ProfileManager::ProfileManager(NetController *net)
{
    netController = net;
}

int ProfileManager::SyncProfile()
{
    String path = "/api/profiles/" + netController->GetIPAddressStr();
    int rspCode = netController->Get(path.c_str());
    if(rspCode == 200)
    {
        String rspBody = netController->GetResponseBody();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, rspBody);

        grndMoistureThreshold = doc["minGrndMoisture"];
        desiredGrndMoisture = doc["maxGrndMoisture"];
    }
    return (rspCode == 200) ? 1 : -1;
}

bool ProfileManager::GrndMoistureBelowThreshold(float grndMoisture)
{
    return grndMoisture <= grndMoistureThreshold;
}

bool ProfileManager::GrndMoistureWithinRange(float grndMoisture)
{
    return grndMoisture >= (desiredGrndMoisture - margin);
}

float ProfileManager::GetMinGrndMoisture()
{
    return grndMoistureThreshold;
}

float ProfileManager::GetMaxGrndMoisture()
{
    return desiredGrndMoisture;
}