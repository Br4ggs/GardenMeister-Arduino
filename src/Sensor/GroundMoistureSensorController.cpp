#include "GroundMoistureSensorController.h"

GroundMoistureSensorController::GroundMoistureSensorController()
{
    pinMode(SENSOR_PIN, INPUT);
    DEBUG_LOGLN("Initialized ground moisture sensor");
}

int GroundMoistureSensorController::MeasureSensor()
{
    sensorValue = analogRead(SENSOR_PIN);
    //if sensorValue is not in range display error message
    return 1;
}

float GroundMoistureSensorController::GetSensorData(int type)
{
    return sensorValue;
}