#include <Arduino.h>
#include "stdlib.h"
#include "WaterPumpController.h"
#include "NetController.h"
#include "SensorManager.h"
#include "ProfileManager.h"

//NEVER DO ANY INITIALIZATION BEFORE SETUP!!

const long LOOP_DELAY = 5000;
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
  DEBUG_LOGLN("----PROFILE----");
  int code = profileManager->SyncProfile();
  DEBUG_LOGLN(code);
  DEBUG_LOGLN(profileManager->GetMinGrndMoisture());
  DEBUG_LOGLN(profileManager->GetMaxGrndMoisture());
  DEBUG_LOGLN("----SENSOR-----");

  int status = sensorManager->PerformMeasurement();
  code = sensorManager->SendMeasurements();
  DEBUG_LOGLN(status);
  DEBUG_LOGLN(code);
  DEBUG_LOGLN("---------------");

  float grndMoist = sensorManager->GetGrndMoistureMeasurement();
  float grndMoistMapped = map(grndMoist, 0, 775, 0, 100);
  //TODO: only do this when grndmoist is not -1?
  if(profileManager->GrndMoistureBelowMin(grndMoistMapped) && motorActive == false){
    motorActive = true;
    DEBUG_LOGLN("Pump activated");
  }
  if(profileManager->GrndMoistureAboveMax(grndMoistMapped) && motorActive == true){
    motorActive = false;
    DEBUG_LOGLN("Pump deactivated");
  }
  if(motorActive == true){
    waterPumpController->ActivateMotor();
  }

  delay(LOOP_DELAY);
}