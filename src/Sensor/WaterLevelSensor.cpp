#include "WaterLevelSensor.h"

WaterLevelSensor::WaterLevelSensor()
{
    pinMode(SENSOR_PIN, INPUT);
}

int WaterLevelSensor::MeasureSensor()
{
    sensorValue = digitalRead(SENSOR_PIN);
    DEBUG_LOGLN(sensorValue);
    return 1;
}

float WaterLevelSensor::GetSensorData(int type)
{
    return sensorValue;
}