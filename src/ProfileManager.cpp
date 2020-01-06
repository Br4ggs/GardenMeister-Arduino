#include "ProfileManager.h"

ProfileManager::ProfileManager(NetController *net)
{
    netController = net;
    //TODO: error handling if not reachable or wrong status code is returned
    //TODO: error handling keep retrying untill server is reached.
    //TODO: maybe think of moving this to setup, as its kind of obscured here.
    RegisterRegulator();
}

int ProfileManager::RegisterRegulator()
{
    String path = "/api/registerRegulator/" + netController->GetIPAddressStr();
    char contentType[] = "application/json";
    int rspCode = netController->Post(path.c_str(), contentType, "");
    DEBUG_LOG(rspCode);
    return 1;
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