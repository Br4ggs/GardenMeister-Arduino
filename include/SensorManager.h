#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "stdlib.h"
#include "GroundMoistureSensorController.h"
#include "DHT11SensorController.h"
#include "WaterLevelSensor.h"
#include "NetController.h"
//Management class responsible for orchestrating and controlling
//the different sensors used by the Arduino.
//Can send measurement data to the server for permanent storage.
class SensorManager
{
private:
    ISensor *grndSensor;
    ISensor *dht11Sensor;
    ISensor *waterLevelSensor;
    NetController *netController;
public:
    SensorManager(NetController *net);
    //Measure data from all sensors on Arduino.
    int PerformMeasurement();
    //Send last retrieved measurements to server.
    int SendMeasurements();
    float GetGrndMoistureMeasurement();
    float GetHumidityMeasurement();
    float GetTemperatureMeasurement();
    bool WaterTankEmpty();
};

#endif