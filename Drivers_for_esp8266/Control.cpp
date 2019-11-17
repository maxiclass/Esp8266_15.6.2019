#include "ShareableResources.h"
#include "Handle_Web.h"
#include "MpuControl.h"
#include "Math.h"


void vSystemDroneControl() // this function must be handled by a interrupt rutine
{

	int x, y, z;                        //three axis acceleration data
	double roll = 0.00, pitch = 0.00;       //Roll & Pitch are the angles which rotate by the axis X and y

		double x_Buff = fGetMpuStrAx();
		double y_Buff = fGetMpuStrAy();
		double z_Buff = fGetMpuStrAz();
		roll = atan2(y_Buff, z_Buff) * 57.3;
		pitch = atan2((-x_Buff), sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;

		u32ControlMotorSpeed(roll, roll, pitch, pitch);


}