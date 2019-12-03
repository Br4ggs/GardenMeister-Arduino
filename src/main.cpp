#include <Arduino.h>
#include "stdlib.h"
#include "ISensor.h"
#include "GroundMoistureSensorController.h"
#include "DHT11SensorController.h"
#include "WaterPumpController.h"
#include "NetController.h"

//NEVER DO ANY INITIALIZATION BEFORE SETUP!!

//motor and sensors cannot function all at the same time
//luckily we never have to do that
//so we can first measure the sensors
//then turn on the motor for a certain amount of time

//collect air moisture and temperature data
//collect ground moisture data
//  if ground moisture level is too low:
//    give water for X amount of seconds
//
//send data to server
//check plant profile with server
//send ok status check(?)
//delay for x amount of seconds

const long LOOP_DELAY = 2000;

WaterPumpController *waterPumpController;

ISensor *grndSensor;
ISensor *dht11Sensor;

NetController *netController;

void setup() {
#ifdef REGULATOR_DEBUG
  Serial.begin(BAUD_RATE);
  DEBUG_LOG("---RUNNING REGULATOR IN DEBUG MODE---");
#endif

  waterPumpController = new WaterPumpController();
  grndSensor = new GroundMoistureSensorController();
  dht11Sensor = new DHT11SensorController();
  netController = new NetController();
}

void loop() {
  DEBUG_LOG("---------------");

  // char path[] = "/api/todoitems";
  // char postData[] = "{\"name\":\"Arduino Test\",\"isComplete\":true}";
  // char contentType[] = "application/json";
  // String rsp = netController->Get(path);
  // String rsp = netController->Post(path, postData, contentType);

  // DEBUG_LOG("---RESPONSE---");
  // DEBUG_LOG(rsp);

  // DEBUG_LOG("GROUND SENSOR");
  // grndSensor->MeasureSensor();
  // int sensorData = grndSensor->GetSensorData();
  // DEBUG_LOG("ground moisture:");
  // DEBUG_LOG(sensorData);

  // DEBUG_LOG("---------------");

  // DEBUG_LOG("DHT11 SENSOR");
  // dht11Sensor->MeasureSensor();
  // float humidityData = dht11Sensor->GetSensorData(DHT11data::HUMIDITY);
  // float temperatureData = dht11Sensor->GetSensorData(DHT11data::TEMPERATURE);
  // DEBUG_LOG("humidity:");
  // DEBUG_LOG(humidityData);
  // DEBUG_LOG("temperature");
  // DEBUG_LOG(temperatureData);

  delay(LOOP_DELAY);
}