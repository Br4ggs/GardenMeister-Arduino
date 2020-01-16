/**
 * Initial author: Emiel van den Brink
 **/

#ifndef DHT11SENSORCONTROLLER_H
#define DHT11SENSORCONTROLLER_H

#include "stdlib.h"
#include "ISensor.h"
#include "DHT.h"

//Helper enum class for specifying the type of data.
//Used as argument for the GetSensorData() method.
enum DHT11data
{
    HUMIDITY = 0,
    TEMPERATURE = 1
};

//Controller class responsible for measuring, storing and sanitizing
//measurements made by DHT11 sensors.
//Implements the ISensor base class.
class DHT11SensorController : public ISensor
{
private:
    const int SENSOR_DELAY = 3000;
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