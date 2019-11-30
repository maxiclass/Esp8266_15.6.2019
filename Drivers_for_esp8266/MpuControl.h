
#include <cstdint>
#include "MPU9255.h"//include MPU9255 library

#define gravity 9.81 // 1g ~ 9.81 m/s^2
#define magnetometer_cal 0.06 //magnetometer calibration


extern void vprint_Mpu_data(); 
extern void vInit_Mpu();
extern void vProcess_Mpu_data();


extern int16_t gX_offset ;//gyroscope X axis offset
extern int16_t gY_offset ;//gyroscope Y axis offset
extern int16_t gZ_offset ;//gyroscope Z axis offset

extern int16_t aX_offset ;//accelerometer X axis offset
extern int16_t aY_offset ;//accelerometer Y axis offset
extern int16_t aZ_offset ;//accelerometer Z axis offset

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



extern double dGetMpuStrPhi();
extern double dGetMpuStrTheta();
extern double dGetMpuStrPsi();


extern void vMadgwickFilterControl();
extern void vPrintEulerAngles();
