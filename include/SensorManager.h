#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "stdlib.h"
#include "GroundMoistureSensorController.h"
#include "DHT11SensorController.h"
#include "WaterLevelSensor.h"
#include "NetController.h"

class SensorManager
{
private:
    ISensor *grndSensor;
    ISensor *dht11Sensor;
    ISensor *waterLevelSensor;
    NetController *netController;
public:
    SensorManager(NetController *net);
    int PerformMeasurement();
    int SendMeasurements();
    float GetGrndMoistureMeasurement();
    float GetHumidityMeasurement();
    float GetTemperatureMeasurement();
    bool WaterTankEmpty();
};

#endif