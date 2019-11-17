#pragma once
#include "index.h"
#include "ESP8266WebServer.h"
#include <cstdint>
#include <stdlib.h>
#include "ShareableResources.h"
#include <Servo.h>                //including the servo library
#include "Motors.h"
#include "Control.h"
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
const int red = D6;
const int green = D7;
const int blue = D8;
const int Motor4PIN = D5;

//Master Functions
extern void InitTimer1(void);
void vDoIsr1Sec(void);
extern void ScheduleTime1(void);
extern void DriversInit(void);


extern void connectToWiFi(void);
extern void htmlIndex(void);
extern void setupServer(void);
extern void HandleWebClient(void);

extern void redFunction(void);
extern void greenFunction(void);
extern void blueFunction(void);
extern void Motor4Function(void);
extern void MoveServoFunction(void);

//functions for sending web data from MPU -> ACC
extern void vSend_Mpu_Ax_to_web(void);
extern void vSend_Mpu_Ay_to_web(void);
extern void vSend_Mpu_Az_to_web(void);

//functions for sending web data from MPU -> GYR
extern void vSend_Mpu_Gx_to_web(void);
extern void vSend_Mpu_Gy_to_web(void);
extern void vSend_Mpu_Gz_to_web(void);

//functions for sending web data from MPU -> MAG
extern void vSend_Mpu_Mx_to_web(void);
extern void vSend_Mpu_My_to_web(void);
extern void vSend_Mpu_Mz_to_web(void);