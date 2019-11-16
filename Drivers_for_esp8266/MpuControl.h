

#define gravity 9.81 // 1g ~ 9.81 m/s^2
#define magnetometer_cal 0.06 //magnetometer calibration



extern void vprint_Mpu_data(); 
extern void vInit_Mpu();
extern void vProcess_Mpu_data();

extern float fGetMpuStrAx();
extern float fGetMpuStrAy();
extern float fGetMpuStrAz();





 class MPU_PROCESSING
{
public :
	
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

private :

};