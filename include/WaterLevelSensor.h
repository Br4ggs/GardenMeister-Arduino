#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include "stdlib.h"
#include "ISensor.h"

class WaterLevelSensor : public ISensor
{
private:
    int SENSOR_PIN = 3;
    int sensorValue;
public:
    WaterLevelSensor();
    int MeasureSensor();
    float GetSensorData(int type);
};

#endif