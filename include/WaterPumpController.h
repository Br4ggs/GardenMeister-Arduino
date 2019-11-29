#ifndef WATERPUMPCONTROLLER_H
#define WATERPUMPCONTROLLER_H

#include "stdlib.h"

class WaterPumpController
{
private:
    const int PUMP_PIN = 1;
    byte motorSpeed = 255;
    int motorTime = 3000;
public:
    WaterPumpController();
    void SetMotorSpeed(byte speed);
    void SetMotorDuration(int time);
    void ActivateMotor();
};

#endif