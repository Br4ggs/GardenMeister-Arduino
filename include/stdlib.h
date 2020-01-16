/**
 * Initial author: Emiel van den Brink
 **/

#ifndef STDLIB_H
#define STDLIB_H

#include <Arduino.h>

//comment this out for production release!
#define REGULATOR_DEBUG
//#define NET_DEBUG

#ifdef REGULATOR_DEBUG
 #define DEBUG_LOGLN(x) Serial.println (x)
 #define DEBUG_LOG(x) Serial.print (x)
 #define BAUD_RATE 9600
#else
 #define DEBUG_LOGLN(x)
 #define DEBUG_LOG(x)
#endif

#endif