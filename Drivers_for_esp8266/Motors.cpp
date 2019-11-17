
#include "Motors.h"	

Servo ServoMotor_Front_Left;   // Servo config as servo class
Servo ServoMotor_Front_Right;
Servo ServoMotor_Back_Left;
Servo ServoMotor_Back_Right;

Motor_A2212 Motor_Front_Left; // Motor config as Motor_A2212 class
Motor_A2212 Motor_Front_Right;
Motor_A2212 Motor_Back_Left;
Motor_A2212 Motor_Back_Right;

void vCustomizeMotorClass()
{
	//CONFIG Motor 1 -> Front_Left
	Motor_Front_Left.u8ServoPin = DIGITAL4;
	Motor_Front_Left.u8MotorState = Motor_Front_Left.Init;

	//CONFIG Motor 2 -> Front_Right
	Motor_Front_Right.u8ServoPin = DIGITAL5;
	Motor_Front_Right.u8MotorState = Motor_Front_Right.Init;

	//CONFIG Motor 3 -> Back_Left
	Motor_Back_Left.u8ServoPin = DIGITAL6;
	Motor_Back_Left.u8MotorState = Motor_Back_Left.Init;
	//CONFIG Motor 4 -> Back_Right 
	Motor_Back_Right.u8ServoPin = DIGITAL7;
	Motor_Back_Right.u8MotorState = Motor_Back_Right.Init;
}



void vInitServoMotors()
{
	pinMode(Motor_Front_Left.u8ServoPin, OUTPUT);
	pinMode(Motor_Front_Right.u8ServoPin, OUTPUT);
	pinMode(Motor_Back_Left.u8ServoPin, OUTPUT);
	pinMode(Motor_Back_Right.u8ServoPin, OUTPUT);


	ServoMotor_Front_Left.attach(Motor_Front_Left.u8ServoPin);
	ServoMotor_Front_Left.write(0);

	ServoMotor_Front_Right.attach(Motor_Front_Right.u8ServoPin);
	ServoMotor_Front_Right.write(0);

	ServoMotor_Back_Left.attach(Motor_Back_Left.u8ServoPin);
	ServoMotor_Back_Left.write(0);

	ServoMotor_Back_Right.attach(Motor_Back_Right.u8ServoPin);
	ServoMotor_Back_Right.write(0);
}


