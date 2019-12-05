#include <Arduino.h>
#include "stdlib.h"
#include "WaterPumpController.h"
#include "NetController.h"
#include "SensorManager.h"
#include "ProfileManager.h"

//TODO: add documentation for classes.

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
ProfileManager *profileManager;

void setup() {
#ifdef REGULATOR_DEBUG
  Serial.begin(BAUD_RATE);
  DEBUG_LOGLN("---RUNNING REGULATOR IN DEBUG MODE---");
#endif

  waterPumpController = new WaterPumpController();
  netController = new NetController();
  sensorManager = new SensorManager(netController);
  profileManager = new ProfileManager(netController);
}

void loop() {
  DEBUG_LOGLN("---------------");

  // sensorManager->PerformMeasurement();
  // float grndMoist = sensorManager->GetGrndMoistureMeasurement();
  // float humidity = sensorManager->GetHumidityMeasurement();
  // float temperature = sensorManager->GetTemperatureMeasurement();

  // DEBUG_LOG("GROUND MOISTURE: ");
  // DEBUG_LOGLN(grndMoist);
  // DEBUG_LOG("HUMIDITY:        ");
  // DEBUG_LOGLN(humidity);
  // DEBUG_LOG("TEMPERATURE:     ");
  // DEBUG_LOGLN(temperature);

  // int rsp = sensorManager->SendMeasurements();
  // DEBUG_LOG("responded with status code: ");
  // DEBUG_LOGLN(rsp);

  // DEBUG_LOGLN("---------------");

  // float grndTest = 34.0f;
  // bool testResult = profileManager->GrndMoistureWithinRange(grndTest);
  // DEBUG_LOGLN(testResult);
  // grndTest = 35.0f;
  // testResult = profileManager->GrndMoistureWithinRange(grndTest);
  // DEBUG_LOGLN(testResult);
  // grndTest = 51.0f;
  // testResult = profileManager->GrndMoistureWithinRange(grndTest);
  // DEBUG_LOGLN(testResult);

  delay(LOOP_DELAY);
}