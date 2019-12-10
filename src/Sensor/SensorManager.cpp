#include "SensorManager.h"

SensorManager::SensorManager(NetController *net)
{
    grndSensor = new GroundMoistureSensorController();
    dht11Sensor = new DHT11SensorController();
    netController = net;
}

int SensorManager::PerformMeasurement()
{
    int grndCode = grndSensor->MeasureSensor();
    int dht11Code = dht11Sensor->MeasureSensor();

    DEBUG_LOG("GRND STATUS: ");
    DEBUG_LOGLN(grndCode);
    DEBUG_LOG("DHT11 STATUS: ");
    DEBUG_LOGLN(dht11Code);

    return (grndCode == -1 || dht11Code == -1) ? -1 : 1;
}

int SensorManager::SendMeasurements()
{
    String ip = netController->GetIPAddressStr();
    //TODO: use json formatter
    float temperature = GetTemperatureMeasurement();
    float humidity = GetHumidityMeasurement();
    float grndMoisture = GetGrndMoistureMeasurement();

    //this needs to happen in the individual sensor controllers
    // if(isnan(temperature))
    //     temperature = -1;

    // if(isnan(humidity))
    //     humidity = -1;

    // if(isnan(grndMoisture))
    //     grndMoisture = -1;
    
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

    DEBUG_LOGLN(jsonBody);

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