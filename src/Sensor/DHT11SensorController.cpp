#include "DHT11SensorController.h"

DHT11SensorController::DHT11SensorController()
    : DHTSensor(SENSOR_PIN, DHT_TYPE)
{
    DHTSensor.begin();
}

int DHT11SensorController::MeasureSensor()
{
    humidityValue = DHTSensor.readHumidity();
    delay(SENSOR_DELAY);
    temperatureValue = DHTSensor.readTemperature();

    if(isnan(temperatureValue))
        temperatureValue = -1;

    if(isnan(humidityValue))
        humidityValue = -1;
    
    return (temperatureValue == -1 || humidityValue == -1) ? -1 : 1;
}

float DHT11SensorController::GetSensorData(int type)
{
    switch (type)
    {
    case 0:
        return humidityValue;
    case 1:
        return temperatureValue;
    default:
        return -1;
    }
}