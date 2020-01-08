#include <Arduino.h>
#include "stdlib.h"
#include "WaterPumpController.h"
#include "NetController.h"
#include "SensorManager.h"
#include "ProfileManager.h"

//NEVER DO ANY INITIALIZATION BEFORE SETUP!!

const long LOOP_DELAY = 1000;
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

  //TODO: something is wrong with the netcontroller

  waterPumpController = new WaterPumpController();
  netController = new NetController();
  sensorManager = new SensorManager(netController);
  profileManager = new ProfileManager(netController);

  delay(5000);
  DEBUG_LOGLN("starting loop");
  //TODO: error handling if not reachable or wrong status code is returned
  //TODO: error handling keep retrying untill server is reached.
  int code = profileManager->RegisterRegulator();
  DEBUG_LOGLN(code);
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
  DEBUG_LOG("HUMIDITY: ");
  DEBUG_LOGLN(sensorManager->GetHumidityMeasurement());
  DEBUG_LOG("TEMPERATURE: ");
  DEBUG_LOGLN(sensorManager->GetTemperatureMeasurement());
  DEBUG_LOG("GROUND MOISTURE: ");
  DEBUG_LOGLN(sensorManager->GetGrndMoistureMeasurement());
  DEBUG_LOG("WATER LEVEL: ");
  DEBUG_LOGLN(sensorManager->WaterTankEmpty());
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