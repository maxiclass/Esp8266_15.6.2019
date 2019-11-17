#pragma once


#include <Servo.h>    
#include <cstdint>

extern void vInitServoMotors();
extern void vCustomizeMotorClass();

static const uint8_t DIGITAL0 = 16;
static const uint8_t DIGITAL1 = 5;
static const uint8_t DIGITAL2 = 4;
static const uint8_t DIGITAL3 = 0;
static const uint8_t DIGITAL4 = 2;
static const uint8_t DIGITAL5 = 14;
static const uint8_t DIGITAL6 = 12;
static const uint8_t DIGITAL7 = 13;
static const uint8_t DIGITAL8 = 15;
static const uint8_t DIGITAL9 = 3;
static const uint8_t DIGITAL10 = 1;


// define class for all 4 motors
class Motor_A2212
{
public:

	// define variables in order to use the motor
	unsigned char u8MotorState;
	unsigned int u32MinServoValue;
	unsigned int u32MaxServoValue;
	unsigned int u32ServoActualValue;
	unsigned char  u8ServoPin;

	enum eMotorsState
	{
		Init=0,
		Calibration=1,
		Ready=2,
		Running=3,
		FailState=4
	};

	int  GetMotorState	()			{return u8MotorState;	}
	void SetMotorState (int value)	{	 u8MotorState = value; }
	
	int	 GetServoActualValue()		  { return u32ServoActualValue; }
	void SetServoActualValue(int value) {u32ServoActualValue = value;	}

	int	 GetMinServoValue() { return u32MinServoValue; }
	void SetMinServoValue(int value) { u32MinServoValue = value; }

	int	 GetMaxServoValue() { return u32MaxServoValue; }
	void SetMaxServoValue(int value) { u32MaxServoValue = value; }

	void vStartMotorCalibration()
	{
	//TODO
	}

	void vStartMotor()
	{
	//TODO
	}

	void vStopMotor()
	{
	//TODO
	}


private:





};