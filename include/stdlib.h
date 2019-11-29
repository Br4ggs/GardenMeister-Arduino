#ifndef STDLIB_H
#define STDLIB_H

#include <Arduino.h>

//comment this out for production release!
#define REGULATOR_DEBUG

#ifdef REGULATOR_DEBUG
 #define DEBUG_LOG(x) Serial.println (x)
 #define BAUD_RATE 9600
#else
 #define DEBUG_LOG(x)
#endif

#endif