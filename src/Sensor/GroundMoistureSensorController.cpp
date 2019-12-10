#include "GroundMoistureSensorController.h"

GroundMoistureSensorController::GroundMoistureSensorController()
{
    pinMode(SENSOR_PIN, INPUT);
    DEBUG_LOGLN("Initialized ground moisture sensor");
}

int GroundMoistureSensorController::MeasureSensor()
{
    sensorValue = analogRead(SENSOR_PIN);

    if (sensorValue < MIN_OUTPUT || sensorValue > MAX_OUTPUT)
        sensorValue = -1;
    
    return (sensorValue < MIN_OUTPUT || sensorValue > MAX_OUTPUT) ? -1 : 1;
}

float GroundMoistureSensorController::GetSensorData(int type)
{
    return sensorValue;
}