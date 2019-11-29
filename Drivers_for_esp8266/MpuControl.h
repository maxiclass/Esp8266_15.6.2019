
#include <cstdint>
#include "MPU9255.h"//include MPU9255 library

#define gravity 9.81 // 1g ~ 9.81 m/s^2
#define magnetometer_cal 0.06 //magnetometer calibration



extern void vprint_Mpu_data(); 
extern void vInit_Mpu();
extern void vProcess_Mpu_data();

extern void vInit_MpuCalibration();//init MPU calibration

extern float fGetMpuStrAx();
extern float fGetMpuStrAy();
extern float fGetMpuStrAz();

extern float fGetMpuStrGx();
extern float fGetMpuStrGy();
extern float fGetMpuStrGz();

extern float fGetMpuStrMx();
extern float fGetMpuStrMy();
extern float fGetMpuStrMz();

extern int16_t s16GetMpuStrAx();
extern int16_t s16GetMpuStrAy();
extern int16_t s16GetMpuStrAz();

extern int16_t s16GetMpuStrGx();
extern int16_t s16GetMpuStrGy();
extern int16_t s16GetMpuStrGz();

extern int16_t s16GetMpuStrMx();
extern int16_t s16GetMpuStrMy();
extern int16_t s16GetMpuStrMz();

extern void vPIDSystemControl();
extern void vPrintEulerAngles();


 class MPU_PROCESSING
{
public :
	 boolean bMPUInitState=0;
	//float data for Accelerometer processing
	float fAx=0;
	float fAy=0;
	float fAz=0;
	
	//float data for Gyroscope processing
	float fGx=0;
	float fGy=0;
	float fGz=0;

	//float data for Magnetormeter processing
	float fMx=0;
	float fMy=0;
	float fMz=0;

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

private :

};