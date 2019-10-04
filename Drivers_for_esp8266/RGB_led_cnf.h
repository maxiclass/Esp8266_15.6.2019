#pragma once
#include <cstdint>
#include "ESP8266WebServer.h"
#include <stdlib.h>

static const uint8_t D0 = 16;
static const uint8_t D1 = 5;
static const uint8_t D2 = 4;
static const uint8_t D3 = 0;
static const uint8_t D4 = 2;
static const uint8_t D5 = 14;
static const uint8_t D6 = 12;
static const uint8_t D7 = 13;
static const uint8_t D8 = 15;
static const uint8_t D9 = 3;
static const uint8_t D10 = 1;

//create 3 variables that are used to stores the pins to which is the LED
//attached
static const int red = D6;
static const int green = D7;
static const int blue = D8;


extern void redFunction();
extern void blueFunction();
extern void greenFunction();
//HC-sr04 ultrasonic sensor
static const int TrigerSensorHC = D1;
static const int EchoSensorHC = D2;
// defines variables for HC-sr04 ultrasonic sensor
static  float durationSensorHC=0;
static  float distanceSensorHC=0;

extern void SensorDetectionInteruput(void);
extern void SetDistanceLight(float);

extern void InitTimer1(void);
extern void ScheduleTime1(void);

