/**
 * Initial author: Emiel van den Brink
 **/

#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include "stdlib.h"
#include "ISensor.h"

//Controller class responsible for measuring if water level in
//tank is lower than threshold (how low the water level sensor hangs into the tank).
//Implements the ISensor base class.
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