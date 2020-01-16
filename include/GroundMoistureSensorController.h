/**
 * Initial author: Emiel van den Brink
 **/

#ifndef GROUNDMOISTURESENSORCONTROLLER_H
#define GROUNDMOISTURESENSORCONTROLLER_H

#include "stdlib.h"
#include "ISensor.h"

//Controller class responsible for measuring, storing and sanitizing
//measurements made by Grove moisture sensors.
//Implements the ISensor base class.
class GroundMoistureSensorController : public ISensor
{
private:
    const int MIN_OUTPUT = 0;
    const int MAX_OUTPUT = 775;
    const int SENSOR_PIN = A0;
    int sensorValue;
public:
    GroundMoistureSensorController();
    int MeasureSensor();
    float GetSensorData(int type);
};

#endif