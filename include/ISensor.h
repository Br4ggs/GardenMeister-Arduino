#ifndef ISENSOR_H
#define ISENSOR_H

//Abstract base class which represents a sensor which
//can measure one or more values
class ISensor
{
public:
    virtual int MeasureSensor() = 0;
    virtual float GetSensorData(int type = 0) = 0;
};

#endif