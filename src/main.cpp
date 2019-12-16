#include <Arduino.h>
#include "stdlib.h"
#include "WaterPumpController.h"
#include "NetController.h"
#include "SensorManager.h"
#include "ProfileManager.h"

#include "WaterLevelSensor.h"

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
bool motorActive = false;

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
  // int code = profileManager->SyncProfile();
  // DEBUG_LOGLN("---------------");
  // DEBUG_LOGLN(code);
  // DEBUG_LOGLN(profileManager->GetMinGrndMoisture());
  // DEBUG_LOGLN(profileManager->GetMaxGrndMoisture());

  int status = sensorManager->PerformMeasurement();
  
  sensorManager->SendMeasurements();
  
  float grndMoist = sensorManager->GetGrndMoistureMeasurement();

  float grndMoistMapped = map(grndMoist, 0, 700, 0, 100);
  DEBUG_LOGLN(grndMoistMapped);

  if(profileManager->GrndMoistureBelowThreshold(grndMoistMapped) && motorActive == false){
    motorActive = true;
    DEBUG_LOGLN("Motor Activatie");
  }
  if(profileManager->GrndMoistureWithinRange(grndMoistMapped) && motorActive == true){
    motorActive = false;
    DEBUG_LOGLN("Motor Deactiveert");
  }
  if(motorActive == true){
    waterPumpController->ActivateMotor();
  }

  delay(LOOP_DELAY);
}