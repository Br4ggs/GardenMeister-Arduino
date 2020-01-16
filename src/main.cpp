/**
 * Initial author: Emiel van den Brink
 **/

#include <Arduino.h>
#include "stdlib.h"
#include "WaterPumpController.h"
#include "NetController.h"
#include "SensorManager.h"
#include "ProfileManager.h"

//NEVER DO ANY INITIALIZATION BEFORE SETUP!!

const long LOOP_DELAY = 1000*60*10;
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

  delay(5000);
  DEBUG_LOGLN("starting registration");
  
  int code;
  while (code != 200)
  {
    code = profileManager->RegisterRegulator();
    if (code != 200)
    {
      DEBUG_LOGLN("registration failed, retrying in 5 seconds...");
    }
    delay(5000);
  }
  DEBUG_LOGLN("registration succesfull");
}

void loop() {
  DEBUG_LOGLN("----PROFILE----");
  int code = profileManager->SyncProfile();
  DEBUG_LOGLN(code);
  DEBUG_LOGLN(profileManager->GetMinGrndMoisture());
  DEBUG_LOGLN(profileManager->GetMaxGrndMoisture());
  DEBUG_LOGLN("----SENSOR-----");

  int status = sensorManager->PerformMeasurement();
  DEBUG_LOGLN(status);
  DEBUG_LOG("HUMIDITY: ");
  DEBUG_LOGLN(sensorManager->GetHumidityMeasurement());
  DEBUG_LOG("TEMPERATURE: ");
  DEBUG_LOGLN(sensorManager->GetTemperatureMeasurement());
  DEBUG_LOG("GROUND MOISTURE: ");
  DEBUG_LOGLN(sensorManager->GetGrndMoistureMeasurement());
  DEBUG_LOG("WATER LEVEL: ");
  DEBUG_LOGLN(sensorManager->WaterTankEmpty());
  code = sensorManager->SendMeasurements();
  DEBUG_LOGLN(code);
  DEBUG_LOGLN("---------------");

  float grndMoist = sensorManager->GetGrndMoistureMeasurement();
  float grndMoistMapped = map(grndMoist, 0, 775, 0, 100);
  DEBUG_LOG("GROUND MOISTURE MAPPED: ");
  DEBUG_LOGLN(grndMoistMapped);

  if(profileManager->GrndMoistureBelowMin(grndMoistMapped) && motorActive == false)
  {
    motorActive = true;
  }

  if(profileManager->GrndMoistureAboveMax(grndMoistMapped) && motorActive == true)
  {
    motorActive = false;
  }

  if(motorActive == true && !sensorManager->WaterTankEmpty())
  {
    DEBUG_LOGLN("activating motor");
    waterPumpController->ActivateMotor();
  }

  delay(LOOP_DELAY);
}