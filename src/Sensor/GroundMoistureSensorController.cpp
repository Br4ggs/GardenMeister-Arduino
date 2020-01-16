/**
 * Initial author: Emiel van den Brink
 **/

#include "GroundMoistureSensorController.h"

GroundMoistureSensorController::GroundMoistureSensorController()
{
    pinMode(SENSOR_PIN, INPUT);
}

int GroundMoistureSensorController::MeasureSensor()
{
    sensorValue = analogRead(SENSOR_PIN);

    if (sensorValue < MIN_OUTPUT || sensorValue > MAX_OUTPUT)
        sensorValue = -1;
    
    return (sensorValue == -1) ? -1 : 1;
}

float GroundMoistureSensorController::GetSensorData(int type)
{
    return sensorValue;
}