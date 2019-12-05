#include "ProfileManager.h"

ProfileManager::ProfileManager(NetController *net)
{
    netController = net;
}

int SyncProfile()
{
    //TODO: implement
    return -1;
}

bool ProfileManager::GrndMoistureBelowThreshold(float grndMoisture)
{
    return grndMoisture <= grndMoistureThreshold;
}

bool ProfileManager::GrndMoistureWithinRange(float grndMoisture)
{
    return grndMoisture >= (desiredGrndMoisture - margin);
}