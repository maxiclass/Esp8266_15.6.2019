
#include "RGB_led_cnf.h"

volatile unsigned long next;

void SensorDetectionInteruput()
{
	digitalWrite(TrigerSensorHC, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigerSensorHC, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
	durationSensorHC = pulseIn(EchoSensorHC, HIGH);
	// Calculating the distance
	distanceSensorHC = (durationSensorHC * 0.034) / 2;

	Serial.println(distanceSensorHC);
	SetDistanceLight(distanceSensorHC);

}

//set distance light compare with the sensor result
void SetDistanceLight(float distance)
{
	distance = map(distance, 0, 100, 0, 1023);
	if (distance < 30) 
	{
		digitalWrite(red, HIGH);//change the brightness of red
		digitalWrite(blue, LOW);//change the brightness of red
		digitalWrite(green, LOW);//change the brightness of red
	}
	 if ((distance > 30 ) && (distance < 50))
	{
		digitalWrite(red, LOW);//change the brightness of red
		digitalWrite(blue, HIGH);//change the brightness of red
		digitalWrite(green, LOW);//change the brightness of reds of red
	}
	 if ((distance > 50) && (HIGH < 150))
	{
		digitalWrite(red, LOW);//change the brightness of red
		digitalWrite(blue, LOW);//change the brightness of red
		digitalWrite(green, HIGH);//change the brightness of reds of red
	}
	else 
	{
		digitalWrite(red, LOW);//change the brightness of red
		digitalWrite(blue, LOW);//change the brightness of red
		digitalWrite(green, LOW);//change the brightness of reds of red
	}
}

// initialize timer1 
void InitTimer1()
{
	noInterrupts();
	timer0_isr_init();
	timer0_attachInterrupt(ScheduleTime1);
	timer0_write(ESP.getCycleCount() + 5000000); //80Mhz -> 80*10^6 = 1 second
	interrupts();
}

void ScheduleTime1()
{
	SensorDetectionInteruput();
	// Set-up the next interrupt cycle
	timer0_write(ESP.getCycleCount() + 5000000); //80Mhz -> 80*10^6 = 1 second
}

