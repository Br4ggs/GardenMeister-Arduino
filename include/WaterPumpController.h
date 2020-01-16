/**
 * Initial author: Emiel van den Brink
 **/

#ifndef WATERPUMPCONTROLLER_H
#define WATERPUMPCONTROLLER_H

#include "stdlib.h"

//Controller class responsible for controlling the water pump, timing and speed.
class WaterPumpController
{
private:
    const int PUMP_PIN = 1;
    byte motorSpeed = 255;
    int motorTime = 3000;
public:
    WaterPumpController();
    //Set the speed of the motor, using a number between 0 and 255.
    void SetMotorSpeed(byte speed);
    //Set the duration of time the motor will be turned on in miliseconds.
    void SetMotorDuration(int time);
    //Activate the motor for the set duration and speed.
    void ActivateMotor();
};

#endif