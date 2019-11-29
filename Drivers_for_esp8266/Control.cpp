#include "ShareableResources.h"
#include "Handle_Web.h"
#include "MpuControl.h"
#include "Math.h"



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




SystemControl SC;

void vSystemDroneControl() // this function must be handled by a interrupt rutine
{

	int16_t x, y, z;                        //three axis acceleration data
	uint16_t MotorFrontLeftValue;
	uint16_t MotorFrontRightValue;
	uint16_t MotorBackLeftValue;
	uint16_t MotorBackRightValue;


		u32ControlMotorSpeed(MotorFrontLeftValue, MotorFrontRightValue, MotorBackLeftValue, MotorBackRightValue);
}

void vMainPIDDroneControl()
{

	/*///////////////////////////P I D///////////////////////////////////*/
	/*
	SC.roll_desired_angle = mapinput_ROLL, 1000, 2000, -10, 10);
	SC.pitch_desired_angle = map(input_PITCH, 1000, 2000, -10, 10);


	SC.roll_error = Total_angle_y - roll_desired_angle;
	SC.pitch_error = Total_angle_x - pitch_desired_angle;

	SC.roll_pid_p = roll_kp * roll_error;
	SC.pitch_pid_p = pitch_kp * pitch_error;

	if (-3 < SC.roll_error < 3) roll_pid_i = roll_pid_i + (roll_ki * roll_error); }
	if (-3 < pitch_error < 3) { pitch_pid_i = pitch_pid_i + (pitch_ki * pitch_error); }

	roll_pid_d = roll_kd * ((roll_error - roll_previous_error) / elapsedTime);

	roll_PID = roll_pid_p + roll_pid_i + roll_pid_d;
	pitch_PID = pitch_pid_p + pitch_pid_i + pitch_pid_d;



	pwm_R_F = 115 + input_THROTTLE - roll_PID - pitch_PID;
	pwm_R_B = 115 + input_THROTTLE - roll_PID + pitch_PID;
	pwm_L_B = 115 + input_THROTTLE + roll_PID + pitch_PID;
	pwm_L_F = 115 + input_THROTTLE + roll_PID - pitch_PID;
	u32ControlMotorSpeed(MotorFrontLeftValue, MotorFrontRightValue, MotorBackLeftValue, MotorBackRightValue);
	*/

}