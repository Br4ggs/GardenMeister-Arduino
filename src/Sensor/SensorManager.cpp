#include "SensorManager.h"

SensorManager::SensorManager(NetController *net)
{
    grndSensor = new GroundMoistureSensorController();
    dht11Sensor = new DHT11SensorController();
    netController = net;
}

int SensorManager::PerformMeasurement()
{
    grndSensor->MeasureSensor();
    dht11Sensor->MeasureSensor();
    //TODO: if values weren't measured correctly return -1
    return 1;
}

int SensorManager::SendMeasurements()
{
    //TODO
    return -1;
}

float SensorManager::GetGrndMoistureMeasurement()
{
    return grndSensor->GetSensorData();
}

float SensorManager::GetHumidityMeasurement()
{
    return dht11Sensor->GetSensorData(DHT11data::HUMIDITY);
}

float SensorManager::GetTemperatureMeasurement()
{
    return dht11Sensor ->GetSensorData(DHT11data::TEMPERATURE);
}