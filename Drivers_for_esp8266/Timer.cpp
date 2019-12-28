#include "ESP8266WebServer.h"
#include <cstdint>
#include <stdlib.h>
#include "ShareableResources.h"
#include "Servo.h"                //including the servo library
#include "Motors.h"
#include "Control.h"
#include "MpuControl.h"
#include "Handle_Web.h"

 void InitTimer1(void);
 void vDoIsr1Sec(void);
 void ScheduleTime1(void);


// initialize timer1 
void InitTimer1()
{
	noInterrupts();
	timer0_isr_init();
	timer0_attachInterrupt(ScheduleTime1);
	timer0_write(ESP.getCycleCount() + 1600000); //160Mhz -> 160*10^6 = 1 second (160000000)
	interrupts();

}

void ScheduleTime1()
{
	// Set-up the next interrupt cycle
	timer0_write(ESP.getCycleCount() + 160000); //160Mhz -> 160*10^6 = 1 second (160000000)

	u32milisecondsCounter++;
	




	//activate 1 second interruput
	if ((u32milisecondsCounter % 10) == 0)
	{
		


		//vSystemDroneControl();
		noInterrupts();

		//	vMadgwickFilterControl();
		//	vPrintEulerAngles();
		
			vMainPIDDroneControl(vTransformBeta());
			//vprint_Mpu_data();
		interrupts();
		//activate 1 second interruput
		if ((u32milisecondsCounter % 10000) == 0)
		{
			//vSystemDroneControl();
			vDoIsr1Sec();
			//vprint_Mpu_data();

		}


	}




}


void vDoIsr1Sec()
{
	u32secondsCounter++;


	if ((u32secondsCounter % 60) == 0)
	{
		u32minutesCounter++; // TODO 1 minute Isr function
	}
}