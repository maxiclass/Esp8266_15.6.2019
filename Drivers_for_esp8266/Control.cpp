#include "ShareableResources.h"
#include "Handle_Web.h"
#include "MpuControl.h"
#include "Math.h"


void vSystemDroneControl() // this function must be handled by a interrupt rutine
{

	int16_t x, y, z;                        //three axis acceleration data
	uint16_t MotorFrontLeftValue;
	uint16_t MotorFrontRightValue;
	uint16_t MotorBackLeftValue;
	uint16_t MotorBackRightValue;

	//value = map(value, 0, 1024, 0, 180);

	x = s16GetMpuStrAx();
	y = s16GetMpuStrAy();
	z = s16GetMpuStrAz();

	if (y < 0)
	{
		MotorFrontLeftValue = 0;
		MotorFrontRightValue = 0;

		MotorBackLeftValue = map(y , 0,-32767, 0, 180);

		MotorBackRightValue = map(y , 0,-32767, 0, 180);

	}
	else {
		MotorFrontLeftValue = map(y , 0, 32767, 0, 180);

		MotorFrontRightValue = map(y , 0, 32767, 0, 180);


		MotorBackLeftValue = 0;
			MotorBackRightValue = 0;
	}

		u32ControlMotorSpeed(MotorFrontLeftValue, MotorFrontRightValue, MotorBackLeftValue, MotorBackRightValue);
}

