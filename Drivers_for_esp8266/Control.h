#pragma once

#include "Motors.h"
#include <cstdint>

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

	uint16_t MotorFrontLeftValue=0;
	uint16_t MotorFrontRightValue=0;
	uint16_t MotorBackLeftValue=0;
	uint16_t MotorBackRightValue = 0;
private:
};