#include "ShareableResources.h"
#include "Handle_Web.h"
#include "MpuControl.h"
#include "Math.h"
#include "Motors.h"
#include <map>



//////////////////////////////PID FOR ROLL///////////////////////////
float roll_PID, pwm_L_F, pwm_L_B, pwm_R_F, pwm_R_B, roll_error, roll_previous_error;
float roll_pid_p = 0;
float roll_pid_i = 0;
float roll_pid_d = 0;
///////////////////////////////ROLL PID CONSTANTS////////////////////
double roll_kp = 3.2;//3.55
double roll_ki = 0.006;//0.003
double roll_kd = 1.4;//2.05
float roll_desired_angle = 0;     //This is the angle in which we whant the
double pitch_error = 0;
double pitch_PID = 0;

double PsiError = 0;
double ThetaError = 0;
double PhiError = 0;

double PsiActual = 0;
double ThetaActual = 0;
double PhiActual = 0;

uint16_t MotorFrontLeftValue;
uint16_t MotorFrontRightValue;
uint16_t MotorBackLeftValue;
uint16_t MotorBackRightValue;

SystemControl SC;

void vSystemDroneControl() // this function must be handled by a interrupt rutine
{

	int16_t x, y, z;                        //three axis acceleration data



		u32ControlMotorSpeed(MotorFrontLeftValue, MotorFrontRightValue, MotorBackLeftValue, MotorBackRightValue);
}


/*
*Calculate motor speed for each motor of an X quadcopter depending on received instructionsand measures from sensor
* by applying PID control.
*
* (A)(B)x
* \ / z ↑
* X       \ |
* + ----→ y
*  
*/


void vMainPIDDroneControl(double dSetpoint)
{

	float yaw_pid = 0;
	float pitch_pid = 0;
	float roll_pid = 0;
	int   throttle = dSetpoint;

	// Initialize motor commands with throttle
	MotorFrontLeftValue = throttle;
	MotorFrontRightValue = throttle;
	MotorBackLeftValue = throttle;
	MotorBackRightValue = throttle;

	// Do not calculate anything if throttle is 0
		// PID = e.Kp + ∫e.Ki + Δe.Kd
		//yaw_pid = (errors[YAW] * Kp[YAW]) + (error_sum[YAW] * Ki[YAW]) + (delta_err[YAW] * Kd[YAW]);
		//pitch_pid = (errors[PITCH] * Kp[PITCH]) + (error_sum[PITCH] * Ki[PITCH]) + (delta_err[PITCH] * Kd[PITCH]);
		//roll_pid = (errors[ROLL] * Kp[ROLL]) + (error_sum[ROLL] * Ki[ROLL]) + (delta_err[ROLL] * Kd[ROLL]);

	roll_pid =  dGetMpuStrPhi();
	pitch_pid=  dGetMpuStrTheta();
	yaw_pid  =  dGetMpuStrPsi();


		// Calculate pulse duration for each ESC
		MotorFrontLeftValue = throttle - roll_pid - pitch_pid + yaw_pid;
		MotorFrontRightValue = throttle + roll_pid - pitch_pid - yaw_pid;
		MotorBackLeftValue = throttle - roll_pid + pitch_pid - yaw_pid;
		MotorBackRightValue = throttle + roll_pid + pitch_pid + yaw_pid;


	u32ControlMotorSpeed(MotorFrontLeftValue, MotorFrontRightValue, MotorBackLeftValue, MotorBackRightValue);


}



