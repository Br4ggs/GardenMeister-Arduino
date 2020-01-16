/**
 * Initial author: Emiel van den Brink
 **/

#include "SensorManager.h"

SensorManager::SensorManager(NetController *net)
{
    waterLevelSensor = new WaterLevelSensor();
    grndSensor = new GroundMoistureSensorController();
    dht11Sensor = new DHT11SensorController();
    netController = net;
}

int SensorManager::PerformMeasurement()
{
    int waterlvlCode = waterLevelSensor->MeasureSensor();
    int grndCode = grndSensor->MeasureSensor();
    int dht11Code = dht11Sensor->MeasureSensor();

    DEBUG_LOG("GRND STATUS: ");
    DEBUG_LOGLN(grndCode);
    DEBUG_LOG("DHT11 STATUS: ");
    DEBUG_LOGLN(dht11Code);

    return (grndCode == -1 || dht11Code == -1) ? -1 : 1;
}

//TODO: ground moisture should be mapped to 0%-100%
int SensorManager::SendMeasurements()
{
    String ip = netController->GetIPAddressStr();
    //TODO: use json formatter
    float temperature = GetTemperatureMeasurement();
    float humidity = GetHumidityMeasurement();
    float grndMoisture = GetGrndMoistureMeasurement();
    bool tankEmpty = WaterTankEmpty();
    
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
    jsonBody += ",";
    
    jsonBody += "\"tankEmpty\":";
    jsonBody += (tankEmpty == 1) ? "true" : "false";
    jsonBody += "}";

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

bool SensorManager::WaterTankEmpty()
{
    return waterLevelSensor->GetSensorData();
}