/**
 * Initial author: Emiel van den Brink
 **/

#ifndef ISENSOR_H
#define ISENSOR_H

//Abstract base class which represents a sensor which
//can measure one or more values.
class ISensor
{
public:
    //Measures the specified sensor and stores the measurements internally.
    virtual int MeasureSensor() = 0;
    //Get the specified result from the last measurement.
    //If the sensor measures more than 1 type of data set the type argument to the required number.
    virtual float GetSensorData(int type = 0) = 0;
};

#endif