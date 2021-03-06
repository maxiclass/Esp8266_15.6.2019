#pragma once
#include "MpuControl.h"

#include  "MadgwickAHRS.h"
#include "ShareableResources.h"

class MPU_PROCESSING
{
public:
	boolean bMPUCalibrationDone = false;
	//float data for Accelerometer processing
	float fAx = 0;
	float fAy = 0;
	float fAz = 0;

	//float data for Gyroscope processing
	float fGx = 0;
	float fGy = 0;
	float fGz = 0;

	//float data for Magnetormeter processing
	float fMx = 0;
	float fMy = 0;
	float fMz = 0;

	//float data for Temperature processing
	float fTemperature = 0;

	double R11 = 0;
	double R21 = 0;
	double R31 = 0;
	double R32 = 0;
	double R33 = 0;

	double phi = 0;
	double theta = 0;
	double psi = 0;

private:

};

MPU9255 mpu;
MPU_PROCESSING mpuprocessing;
float rad_to_deg = (180 / M_PI);


float elapsedTime, timenow, timePrev;

 double phiLastValue =0;
 double thetaLastValue=0;
 double psiLastValue=0;

 double phiNewValue = 0;
 double thetaNewValue = 0;
 double psiNewValue = 0;


 const int analogPin = A0;



int16_t gX_offset = 0;//gyroscope X axis offset
int16_t gY_offset = 0;//gyroscope Y axis offset
int16_t gZ_offset = 0;//gyroscope Z axis offset

int16_t aX_offset = 0;//accelerometer X axis offset
int16_t aY_offset = 0;//accelerometer Y axis offset
int16_t aZ_offset = 0;//accelerometer Z axis offset


#define         RATIO_ACC       (4./32767.)
#define         RATIO_GYRO      ((1000./32767.)*(M_PI/180.))
//#define         RATIO_GYRO      (1000./32767.)
#define         RATIO_MAG       (48./32767.)

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
	mpu.disable_motion_interrput();
	

}


void vInit_MpuCalibration()//init MPU calibration
{ //set bandwidths to 5Hz to reduce the noise
	mpu.set_acc_bandwidth(acc_5Hz);
	mpu.set_gyro_bandwidth(gyro_5Hz);

	//update flags

	//gyroscope
	bool update_gX = true;
	bool update_gY = true;
	bool update_gZ = true;

	//accelerometer
	bool update_aX = true;
	bool update_aY = true;
	bool update_aZ = true;

	//discard the first reading
	mpu.read_acc();
	mpu.read_gyro();
	delay(10);

	while (1)//offset adjusting loop
	{
		mpu.read_acc();
		mpu.read_gyro();
		//-------- adjust accelerometer X axis offset ----------

		if (mpu.ax > 0 && update_aX == true)//if X axis readings are greater than 0
		{
			aX_offset--;//decrement offset
		}


		if (mpu.ax < 0 && update_aX == true)
		{
			aX_offset++;//increment offset
		}

		//-------- adjust accelerometer Y axis offset ----------

		if (mpu.ay > 0 && update_aY == true)//if X axis readings are greater than 0
		{
			aY_offset--;//decrement offset
		}

		if (mpu.ay < 0 && update_aY == true)
		{
			aY_offset++;//increment offset
		}

		//-------- adjust accelerometer Z axis offset ----------

		if (mpu.az > 0 && update_aZ == true)//if X axis readings are greater than 0
		{
			aZ_offset--;//decrement offset
		}

		if (mpu.az < 0 && update_aZ == true)
		{
			aZ_offset++;//increment offset
		}

		//-------- adjust gyroscope X axis offset ----------

		if (mpu.gx > 0 && update_gX == true)//if X axis readings are greater than 0
		{
			gX_offset--;//decrement offset
		}

		if (mpu.gx < 0 && update_gX == true)
		{
			gX_offset++;//increment offset
		}

		//-------- adjust gyroscope Y axis offset ----------

		if (mpu.gy > 0 && update_gY == true)//if X axis readings are greater than 0
		{
			gY_offset--;//decrement offset
		}

		if (mpu.gy < 0 && update_gY == true)
		{
			gY_offset++;//increment offset
		}

		//-------- adjust gyroscope Z axis offset ----------

		if (mpu.gz > 0 && update_gZ == true)//if X axis readings are greater than 0
		{
			gZ_offset--;//decrement offset
		}

		if (mpu.gz < 0 && update_gZ == true)
		{
			gZ_offset++;//increment offset
		}


		//set new offset
		if (update_gX == true)
		{
			mpu.set_gyro_offset(X_axis, gX_offset);
		}

		if (update_gY == true)
		{
			mpu.set_gyro_offset(Y_axis, gY_offset);
		}

		if (update_gZ == true)
		{
			mpu.set_gyro_offset(Z_axis, gZ_offset);
		}

		if (update_aX == true)
		{
			mpu.set_acc_offset(X_axis, aX_offset);
		}

		if (update_aY == true)
		{
			mpu.set_acc_offset(Y_axis, aY_offset);
		}

		if (update_aZ == true)
		{
			mpu.set_acc_offset(Z_axis, aZ_offset);
		}

		//------ Check if each axis is adjusted -----
		const short maximum_error = 5;//set maximum deviation to 5 LSB
		if ((mpu.ax - maximum_error) <= 0)
		{

		}

		if ((abs(mpu.ax) - maximum_error) <= 0)
		{
			update_aX = false;
		}

		if ((abs(mpu.ay) - maximum_error) <= 0)
		{
			update_aY = false;
		}

		if ((abs(mpu.az) - maximum_error) <= 0)
		{
			update_aZ = false;
		}

		if ((abs(mpu.gx) - maximum_error) <= 0)
		{
			update_gX = false;
		}

		if ((abs(mpu.gy) - maximum_error) <= 0)
		{
			update_gY = false;
		}

		if ((abs(mpu.gz) - maximum_error) <= 0)
		{
			update_gZ = false;
		}


		//------ Adjust procedure end condition ------
		if (update_gX == false && update_gY == false && update_gZ == false && update_aX == false && update_aY == false && update_aZ == false)
		{
			break;
		}

		delay(10);
	}
	//print the output values :
	Serial.println("Offset cancellation complete!");
	Serial.println();
	Serial.print("Accelerometer offset:  X: ");
	Serial.print(aX_offset);
	Serial.print("  Y: ");
	Serial.print(aY_offset);
	Serial.print("  Z: ");
	Serial.println(aZ_offset);
	Serial.print("Gyroscope offset:   X: ");
	Serial.print(gX_offset);
	Serial.print("  Y: ");
	Serial.print(gY_offset);
	Serial.print("  Z: ");
	Serial.println(gZ_offset);
	Serial.println();

	mpuprocessing.bMPUCalibrationDone = true;

}

void vprint_Mpu_data()//read and print raw data from the sensors
{
	vProcess_Mpu_data();
	
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
double dGetMpuStrPhi()
{
	return mpuprocessing.phi;
}
double dGetMpuStrTheta()
{
	return mpuprocessing.theta;
}
double  dGetMpuStrPsi()
{
	return  mpuprocessing.psi;

}



void vProcess_Mpu_data()//read and process data from the sensors
{
	mpu.read_acc();
	mpu.read_gyro();
	mpu.read_mag();
	

	//procces accelerometer row data into meaningful data
	if (scale_2g)
	{
		mpuprocessing.fAx = (((float)(mpu.ax  /* + aX_offset */)) / 16384) * gravity;
		mpuprocessing.fAy = (((float)(mpu.ay  /* +  aY_offset*/)) / 16384) * gravity;
		mpuprocessing.fAz = (((float)(mpu.az  /* +  aZ_offset*/)) / 16384) * gravity;
	}
	if (scale_4g)
	{
		mpuprocessing.fAx = (((float)(mpu.ax  /* +  aX_offset*/)) / 8192) * gravity;
		mpuprocessing.fAy = (((float)(mpu.ay  /* +  aY_offset*/)) / 8192) * gravity;
		mpuprocessing.fAz = (((float)(mpu.az  /* +  aZ_offset*/)) / 8192) * gravity;
	}
	if (scale_8g)
	{
		mpuprocessing.fAx = (((float)(mpu.ax  /* +  aX_offset*/)) / 4096) * gravity;
		mpuprocessing.fAy = (((float)(mpu.ay  /* +  aY_offset*/)) / 4096) * gravity;
		mpuprocessing.fAz = (((float)(mpu.az  /* +  aZ_offset*/)) / 4096) * gravity;
	}
	if (scale_16g)
	{
		mpuprocessing.fAx = (((float)(mpu.ax  /* +  aX_offset*/)) / 2048) * gravity;
		mpuprocessing.fAy = (((float)(mpu.ay  /* +  aY_offset*/)) / 2048) * gravity;
		mpuprocessing.fAz = (((float)(mpu.az  /* +  aZ_offset*/)) / 2048) * gravity;
	}

	//procces gyroscope row data into meaningful data

	if (scale_250dps)
	{
		mpuprocessing.fGx = ((float)(mpu.gx  /* +gX_offset */  ) / 131);
		mpuprocessing.fGy = ((float)(mpu.gy  /* +gY_offset */  ) / 131);
		mpuprocessing.fGz = ((float)(mpu.gz  /* +gZ_offset */  ) / 131);
	}
	if (scale_500dps)
	{
		mpuprocessing.fGx = ((float)(mpu.gx  /* +gX_offset */  ) / 65.5);
		mpuprocessing.fGy = ((float)(mpu.gy  /* +gY_offset */  ) / 65.5);
		mpuprocessing.fGz = ((float)(mpu.gz  /* +gZ_offset */  ) / 65.5);
	}
	if (scale_1000dps)
	{
		mpuprocessing.fGx = ((float)(mpu.gx  /* +gX_offset */  ) / 32.8);
		mpuprocessing.fGy = ((float)(mpu.gy  /* +gY_offset */  ) / 32.8);
		mpuprocessing.fGz = ((float)(mpu.gz  /* +gZ_offset */  ) / 32.8);
	}
	if (scale_2000dps)
	{
		mpuprocessing.fGx = ((float)(mpu.gx  /* +gX_offset */  ) / 16.4);
		mpuprocessing.fGy = ((float)(mpu.gy  /* +gY_offset */  ) / 16.4);
		mpuprocessing.fGz = ((float)(mpu.gz  /* +gZ_offset */  ) / 16.4);
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


void vMadgwickFilterControl()
{
   if (	mpuprocessing.bMPUCalibrationDone ==false ) 

   { 
	 vInit_MpuCalibration();
	mpuprocessing.bMPUCalibrationDone = true; //delete this after wdt problem
   }


   else
   {
	    //vProcess_Mpu_data();
	mpu.read_acc();
	mpu.read_gyro();
	mpu.read_mag();

	// Convert into floats
	float ax, ay, az;
	float gx, gy, gz;
	float mx, my, mz;

	ax = mpu.ax * RATIO_ACC;
	ay = mpu.ay * RATIO_ACC;
	az = mpu.az * RATIO_ACC;

	gx = (mpu.gx - 48.4827) * RATIO_GYRO;
	gy = (mpu.gy + 76.3552) * RATIO_GYRO;
	gz = (mpu.gz + 64.3234) * RATIO_GYRO;

	mx = mpu.mx * RATIO_MAG;
	my = mpu.my * RATIO_MAG;
	mz = mpu.mz * RATIO_MAG;


	MadgwickAHRSupdate( gx,  gy,  gz, \
					    ax,  ay,  az,\
					    mx,  my,  mz);

	 mpuprocessing.R11 = 2. * q0 * q0 - 1 + 2. * q1 * q1;
	 mpuprocessing.R21 = 2. * (q1 * q2 - q0 * q3);
	 mpuprocessing.R31 = 2. * (q1 * q3 + q0 * q2);
	 mpuprocessing.R32 = 2. * (q2 * q3 - q0 * q1);
	 mpuprocessing.R33 = 2. * q0 * q0 - 1 + 2. * q3 * q3;

	 //offsetPHI = vTransformBeta();

	 mpuprocessing.phi = (((atan2(mpuprocessing.R32, mpuprocessing.R33)))) * rad_to_deg ;
	 mpuprocessing.theta = (-atan(mpuprocessing.R31 / (sqrt(1 - mpuprocessing.R31 * mpuprocessing.R31)))) * rad_to_deg ;
	 mpuprocessing.psi = (atan2(mpuprocessing.R21, mpuprocessing.R11)) * rad_to_deg;
   }

}

void vPrintEulerAngles()
{
	timePrev = timenow;  // the previous time is stored before the actual time read
	timenow = u32milisecondsCounter;  // actual time read
	elapsedTime = (timenow - timePrev) / 100; //ms

	static int calibration = 10;
	
	 phiNewValue = (float) mpuprocessing.phi;
	 thetaNewValue = (float) mpuprocessing.theta;
	 psiNewValue = (float)  mpuprocessing.psi;

	 /*
	Serial.print(" phi: ");
	Serial.print(phiNewValue - phiLastValue);
	Serial.print("    theta: ");
	Serial.print(thetaNewValue - thetaLastValue);
	Serial.print("    psi: ");
	Serial.println(psiNewValue - psiLastValue);
	*/

	phiLastValue = phiNewValue;
	thetaLastValue = thetaNewValue;
	psiLastValue = psiNewValue;
	//Serial.print(elapsedTime);
	
	
	
		Serial.print(" phi: ");
	Serial.print(mpuprocessing.phi);
	Serial.print("    theta: ");
	Serial.print(mpuprocessing.theta);
	Serial.print("    psi: ");
	Serial.println(mpuprocessing.psi); 
	


}


int16_t vTransformBeta()
{
	static int16_t beta;
int val = analogRead(analogPin);  // read the input pin
beta = map(val, 0, 1023, 0, 100);

//    Serial.println(beta);          // debug value

return beta;
}