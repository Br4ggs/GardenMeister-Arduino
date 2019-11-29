#include "WaterPumpController.h"

WaterPumpController::WaterPumpController()
{
    pinMode(PUMP_PIN, OUTPUT);
}

void WaterPumpController::SetMotorSpeed(byte speed)
{
    motorSpeed = speed;
}

void WaterPumpController::SetMotorDuration(int time)
{
    motorTime = time;
}

void WaterPumpController::ActivateMotor()
{
    analogWrite(PUMP_PIN, motorSpeed);
    delay(motorTime);
    analogWrite(PUMP_PIN, 0);
}