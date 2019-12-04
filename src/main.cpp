#include <Arduino.h>
#include "stdlib.h"
#include "WaterPumpController.h"
#include "NetController.h"
#include "SensorManager.h"

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
NetController *netController;
SensorManager *sensorManager;

void setup() {
#ifdef REGULATOR_DEBUG
  Serial.begin(BAUD_RATE);
  DEBUG_LOGLN("---RUNNING REGULATOR IN DEBUG MODE---");
#endif

  waterPumpController = new WaterPumpController();
  netController = new NetController();
  sensorManager = new SensorManager(netController);
}

void loop() {
  DEBUG_LOGLN("---------------");

  sensorManager->PerformMeasurement();
  float grndMoist = sensorManager->GetGrndMoistureMeasurement();
  float humidity = sensorManager->GetHumidityMeasurement();
  float temperature = sensorManager->GetTemperatureMeasurement();

  DEBUG_LOG("GROUND MOISTURE: ");
  DEBUG_LOGLN(grndMoist);
  DEBUG_LOG("HUMIDITY:        ");
  DEBUG_LOGLN(humidity);
  DEBUG_LOG("TEMPERATURE:     ");
  DEBUG_LOGLN(temperature);

  // char path[] = "/api/todoitems";
  // char postData[] = "{\"name\":\"Arduino Test\",\"isComplete\":true}";
  // char contentType[] = "application/json";
  // String rsp = netController->Get(path);
  // String rsp = netController->Post(path, postData, contentType);

  // DEBUG_LOGLN("---RESPONSE---");
  // DEBUG_LOGLN(rsp);

  // DEBUG_LOGLN("GROUND SENSOR");
  // grndSensor->MeasureSensor();
  // int sensorData = grndSensor->GetSensorData();
  // DEBUG_LOGLN("ground moisture:");
  // DEBUG_LOGLN(sensorData);

  // DEBUG_LOGLN("---------------");

  // DEBUG_LOGLN("DHT11 SENSOR");
  // dht11Sensor->MeasureSensor();
  // float humidityData = dht11Sensor->GetSensorData(DHT11data::HUMIDITY);
  // float temperatureData = dht11Sensor->GetSensorData(DHT11data::TEMPERATURE);
  // DEBUG_LOGLN("humidity:");
  // DEBUG_LOGLN(humidityData);
  // DEBUG_LOGLN("temperature");
  // DEBUG_LOGLN(temperatureData);

  delay(LOOP_DELAY);
}