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
    //if sensorValue is not in range display error message
    //is NAN
    return 1;
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