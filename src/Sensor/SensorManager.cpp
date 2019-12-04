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
    String ip = netController->GetIPAddressStr();
    //TODO: add error handling if these are NaN
    float temperature = GetTemperatureMeasurement();
    float humidity = GetHumidityMeasurement();
    float grndMoisture = GetGrndMoistureMeasurement();
    
    String jsonBody = "{";
    jsonBody += "\"regulatorID\":\"";
    jsonBody += ip;
    jsonBody += "\",";

    jsonBody += "\"temperature\":";
    jsonBody += temperature;
    jsonBody += ",";

    jsonBody += "\"humidity\":";
    jsonBody += humidity;
    jsonBody += ",";

    jsonBody += "\"soilMoisture\":";
    jsonBody += grndMoisture;
    jsonBody += "}";

    //TODO: move these to netcontroller?
    char contentType[] = "application/json";
    char path[] = "/api/measurement";
    int rspCode = netController->Post(path, jsonBody.c_str(), contentType);

    return rspCode;
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
    return dht11Sensor->GetSensorData(DHT11data::TEMPERATURE);
}