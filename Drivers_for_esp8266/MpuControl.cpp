#pragma once

#include "MPU9255.h"//include MPU9255 library


MPU9255 mpu;

void vInit_Mpu()//init MPU reading
{
	mpu.init();



	mpu.enable(Acc_X);
	mpu.enable(Acc_Y);
	mpu.enable(Acc_Z);

	mpu.enable(Gyro_X);
	mpu.enable(Gyro_Y);
	mpu.enable(Gyro_Z);
}

void vprint_Mpu_data()//read and print raw data from the sensors
{
	mpu.read_acc();
	mpu.read_gyro();

	//PRINT ACCELEROSCOPE MEASUREMENT
	Serial.print("AX: ");
	Serial.print(mpu.ax);
	Serial.print("    AY: ");
	Serial.print(mpu.ay);
	Serial.print("    AZ: ");
	Serial.println(mpu.az);

	//PRINT GYROSCOP MEASUREMENT
	Serial.print("GX: ");
	Serial.print(mpu.gx);
	Serial.print("    GY: ");
	Serial.print(mpu.gy);
	Serial.print("    GZ: ");
	Serial.println(mpu.gz);

}