#pragma once

#include "Motors.h"
#include <cstdint>


#define MIN_THROTTLE_VAL 5
#define MAX_THROTTLE_VAL 100

extern void vSystemDroneControl();
extern void vMainPIDDroneControl(double dSetpoint);
class SystemControl
{
public:
	uint16_t roll_desired_angle = 0;
	uint16_t pitch_desired_angle = 0;

	uint16_t roll_error = 0;
	uint16_t pitch_error = 0;

	uint16_t roll_pid_p = 0;
	uint16_t pitch_pid_p = 0;

	double MotorFrontLeftValue=0;
	double MotorFrontRightValue=0;
	double MotorBackLeftValue=0;
	double MotorBackRightValue = 0;
private:
};