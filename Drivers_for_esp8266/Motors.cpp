
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
	Motor_Front_Left.u32MinServoValue = 0;
	Motor_Front_Left.u32MaxServoValue = 0;
	//CONFIG Motor 2 -> Front_Right
	Motor_Front_Right.u8ServoPin = DIGITAL5;
	Motor_Front_Right.u8MotorState = Motor_Front_Right.Init;
	Motor_Front_Right.u32MinServoValue = 0;
	Motor_Front_Right.u32MaxServoValue = 0;
	//CONFIG Motor 3 -> Back_Left
	Motor_Back_Left.u8ServoPin = DIGITAL8;
	Motor_Back_Left.u8MotorState = Motor_Back_Left.Init;
	Motor_Back_Left.u32MinServoValue = 0;
	Motor_Back_Left.u32MaxServoValue = 0;
	//CONFIG Motor 4 -> Back_Right 
	Motor_Back_Right.u8ServoPin = DIGITAL7;
	Motor_Back_Right.u8MotorState = Motor_Back_Right.Init;
	Motor_Back_Right.u32MinServoValue = 0;
	Motor_Back_Right.u32MaxServoValue = 0;
}



void vInitServoMotors()
{
	pinMode(Motor_Front_Left.u8ServoPin, OUTPUT);
	pinMode(Motor_Front_Right.u8ServoPin, OUTPUT);
	pinMode(Motor_Back_Left.u8ServoPin, OUTPUT);
	pinMode(Motor_Back_Right.u8ServoPin, OUTPUT);


	ServoMotor_Front_Left.attach(Motor_Front_Left.u8ServoPin);
	ServoMotor_Front_Left.write(90);

	ServoMotor_Front_Right.attach(Motor_Front_Right.u8ServoPin);
	ServoMotor_Front_Right.write(90);

	ServoMotor_Back_Left.attach(Motor_Back_Left.u8ServoPin);
	ServoMotor_Back_Left.write(90);

	ServoMotor_Back_Right.attach(Motor_Back_Right.u8ServoPin);
	ServoMotor_Back_Right.write(90);
}


void u32ControlMotorSpeed(uint32_t MotorFrontLeftValue, uint32_t MotorFrontRightValue, uint32_t MotorBackLeftValue, uint32_t MotorBackRightValue)
{
	//Motor_Front_Left
	//Motor_Front_Right
	//Motor_Back_Left
	//Motor_Back_Right
		
	Motor_Front_Left.u32ServoValue = MotorFrontLeftValue;
	Motor_Front_Right.u32ServoValue = MotorFrontRightValue;
	Motor_Back_Left.u32ServoValue = MotorBackLeftValue;
	Motor_Back_Right.u32ServoValue = MotorBackRightValue;

	if (Motor_Front_Left.u32ServoValue == 0) { digitalWrite(Motor_Front_Left.u8ServoPin, LOW); }//turn of the motor}
	if (Motor_Front_Right.u32ServoValue == 0) { digitalWrite(Motor_Front_Right.u8ServoPin, LOW); }//turn of the motor}
	if (Motor_Back_Left.u32ServoValue == 0) { digitalWrite(Motor_Back_Left.u8ServoPin, LOW); }//turn of the motor}
	if (Motor_Back_Right.u32ServoValue == 0) { digitalWrite(Motor_Back_Right.u8ServoPin, LOW); }//turn of the motor}


	ServoMotor_Front_Left.write(Motor_Front_Left.u32ServoValue);
	ServoMotor_Front_Right.write(Motor_Front_Right.u32ServoValue);
	ServoMotor_Back_Left.write(Motor_Back_Left.u32ServoValue);

	/*
	Serial.print("MFL: ");
	Serial.print(Motor_Front_Left.u32ServoValue);
	Serial.print("    MFR: ");
	Serial.print(Motor_Front_Right.u32ServoValue);
	Serial.print("    MBL: ");
	Serial.print(Motor_Back_Left.u32ServoValue);
	Serial.print("    MBR: ");
	Serial.println(Motor_Back_Right.u32ServoValue);
	*/

}