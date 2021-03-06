/**
 * Initial author: Emiel van den Brink
 **/

#include "ProfileManager.h"

ProfileManager::ProfileManager(NetController *net)
{
    netController = net;
}

int ProfileManager::RegisterRegulator()
{
    String path = "/api/registerRegulator/" + netController->GetIPAddressStr();
    char data[] = "{}";
    char contentType[] = "application/json";
    int rspCode = netController->Post(path.c_str(), data, contentType);
    return rspCode;
}

int ProfileManager::SyncProfile()
{
    String path = "/api/ipprofiles/" + netController->GetIPAddressStr();
    int rspCode = netController->Get(path.c_str());
    if(rspCode == 200)
    {
        String rspBody = netController->GetResponseBody();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, rspBody);

        minGrndMoisture = doc["minSoilMoisture"];
        maxGrndMoisture = doc["maxSoilMoisture"];
    }
    return rspCode;
}

bool ProfileManager::GrndMoistureBelowMin(float grndMoisture)
{
    return grndMoisture <= minGrndMoisture;
}

bool ProfileManager::GrndMoistureAboveMax(float grndMoisture)
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