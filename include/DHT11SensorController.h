#ifndef DHT11SENSORCONTROLLER_H
#define DHT11SENSORCONTROLLER_H

#include "stdlib.h"
#include "ISensor.h"
#include "DHT.h"

enum DHT11data
{
    HUMIDITY = 0,
    TEMPERATURE = 1
};

class DHT11SensorController : public ISensor
{
private:
    const int SENSOR_DELAY = 1000;
    const int SENSOR_PIN = 2;
    const int DHT_TYPE = DHT11;
    DHT DHTSensor;
    float humidityValue;
    float temperatureValue;
public:
    DHT11SensorController();
    int MeasureSensor();
    float GetSensorData(int type);
};

#endif