#pragma once
#include "MpuControl.h"
#include <cstdint>


MPU9255 mpu;
MPU_PROCESSING mpuprocessing;


void vInit_Mpu()//init MPU reading
{
	mpu.init();



	mpu.enable(Acc_X);
	mpu.enable(Acc_Y);
	mpu.enable(Acc_Z);

	mpu.enable(Gyro_X);
	mpu.enable(Gyro_Y);
	mpu.enable(Gyro_Z);

	mpu.set_acc_scale(scale_2g);//set accelerometer scale
	mpu.set_gyro_scale(scale_250dps);//set gyroscope scale
}

void vprint_Mpu_data()//read and print raw data from the sensors
{
	vProcess_Mpu_data();
	
	//PRINT ACCELEROSCOPE MEASUREMENT
	Serial.print("AX: ");
	Serial.print(mpu.ax);
	Serial.print("    AY: ");
	Serial.print(mpu.ay);
	Serial.print("    AZ: ");
	Serial.println(mpu.az);

	//PRINT ACCELEROSCOPE MEASUREMENT
	Serial.print("AX: ");
	Serial.print(mpuprocessing.fAx);
	Serial.print("    AY: ");
	Serial.print(mpuprocessing.fAy);
	Serial.print("    AZ: ");
	Serial.println(mpuprocessing.fAz);

	//PRINT GYROSCOP MEASUREMENT
	Serial.print("GX: ");
	Serial.print(mpuprocessing.fGx);
	Serial.print("    GY: ");
	Serial.print(mpuprocessing.fGy);
	Serial.print("    GZ: ");
	Serial.println(mpuprocessing.fGz);

	//PRINT MAGNETOMETER MEASUREMENT
	Serial.print("MX: ");
	Serial.print(mpuprocessing.fMx);
	Serial.print("    MY: ");
	Serial.print(mpuprocessing.fMy);
	Serial.print("    MZ: ");
	Serial.println(mpuprocessing.fMz);

	//PRINT TEMPERATURE MEASUREMENT
	Serial.print("Temperature " );
	Serial.println(mpuprocessing.fTemperature);

	//
	
	//fWebAccz = mpuprocessing.fAz;



}


float fGetMpuStrAx()
{
	return mpuprocessing.fAx;
}
float fGetMpuStrAy()
{
	return mpuprocessing.fAy;
}
float  fGetMpuStrAz()
{
	return  mpuprocessing.fAz;
}

float fGetMpuStrGx()
{
	return mpuprocessing.fGx;
}
float fGetMpuStrGy()
{
	return mpuprocessing.fGy;
}
float  fGetMpuStrGz()
{
	return  mpuprocessing.fGz;
}

float fGetMpuStrMx()
{
	return mpuprocessing.fMx;
}
float fGetMpuStrMy()
{
	return mpuprocessing.fMy;
}
float  fGetMpuStrMz()
{
	return  mpuprocessing.fMz;
}






int16_t s16GetMpuStrAx()
{
	return mpu.ax;
}
int16_t s16GetMpuStrAy()
{
	return mpu.ay;
}
int16_t  s16GetMpuStrAz()
{
	return  mpu.az;
}

int16_t s16GetMpuStrGx()
{
	return mpu.gx;
}
int16_t s16GetMpuStrGy()
{
	return mpu.gy;
}
int16_t  s16GetMpuStrGz()
{
	return  mpu.gz;
}

int16_t s16GetMpuStrMx()
{
	return mpu.gx;
}
int16_t s16GetMpuStrMy()
{
	return mpu.gy;
}
int16_t  s16GetMpuStrMz()
{
	return  mpu.gz;
}







void vProcess_Mpu_data()//read and process data from the sensors
{
	mpu.read_acc();
	mpu.read_gyro();
	mpu.read_mag();
	

	//procces accelerometer row data into meaningful data
	if (scale_2g)
	{
		mpuprocessing.fAx = (((float)mpu.ax) / 16384) * gravity;
		mpuprocessing.fAy = (((float)mpu.ay) / 16384) * gravity;
		mpuprocessing.fAz = (((float)mpu.az) / 16384) * gravity;
	}
	if (scale_4g)
	{
		mpuprocessing.fAx = (((float)mpu.ax) / 8192) * gravity;
		mpuprocessing.fAy = (((float)mpu.ay) / 8192) * gravity;
		mpuprocessing.fAz = (((float)mpu.az) / 8192) * gravity;
	}
	if (scale_8g)
	{
		mpuprocessing.fAx = ((float)mpu.ax / 4096) * gravity;
		mpuprocessing.fAy = ((float)mpu.ay / 4096) * gravity;
		mpuprocessing.fAz = ((float)mpu.az / 4096) * gravity;
	}
	if (scale_16g)
	{
		mpuprocessing.fAx = ((float)mpu.ax / 2048) * gravity;
		mpuprocessing.fAy = ((float)mpu.ay / 2048) * gravity;
		mpuprocessing.fAz = ((float)mpu.az / 2048) * gravity;
	}

	//procces gyroscope row data into meaningful data

	if (scale_250dps)
	{
		mpuprocessing.fGx = ((float)mpu.gx / 131);
		mpuprocessing.fGy = ((float)mpu.gy / 131);
		mpuprocessing.fGz = ((float)mpu.gz / 131);
	}
	if (scale_500dps)
	{
		mpuprocessing.fGx = ((float)mpu.gx / 65.5);
		mpuprocessing.fGy = ((float)mpu.gy / 65.5);
		mpuprocessing.fGz = ((float)mpu.gz / 65.5);
	}
	if (scale_1000dps)
	{
		mpuprocessing.fGx = ((float)mpu.gx / 32.8);
		mpuprocessing.fGy = ((float)mpu.gy / 32.8);
		mpuprocessing.fGz = ((float)mpu.gz / 32.8);
	}
	if (scale_2000dps)
	{
		mpuprocessing.fGx = ((float)mpu.gx / 16.4);
		mpuprocessing.fGy = ((float)mpu.gy / 16.4);
		mpuprocessing.fGz = ((float)mpu.gz / 16.4);
	}

	//procces magnetormeter row data into meaningful data
	//To get magnetic flux density in uTach reading has to be multiplied by sensitivity
	//(Constant value different for each axis, stored in ROM), then multiplied by some number(calibration)
	//	and then divided by 0.6 .
	//	(Faced North each axis should output around 31 uT without any metal / walls around
	//		Note : This manetometer has really low initial calibration tolerance : +-500 LSB !!!
	//		Scale of the magnetometer is fixed -> + -4800 uT.
	mpuprocessing.fMx = ((float)mpu.mx * mpu.mx_sensitivity * magnetometer_cal )/ 0.6;
	mpuprocessing.fMy = ((float)mpu.my * mpu.my_sensitivity * magnetometer_cal )/ 0.6;
	mpuprocessing.fMz = ((float)mpu.my * mpu.mz_sensitivity * magnetometer_cal )/ 0.6;

	//procces temperature sensor row data into meaningful data
	mpuprocessing.fTemperature = ((float)mpu.read_temp() )/ 333.87 + 21.0; // Temperature in degrees Centigrade
}



