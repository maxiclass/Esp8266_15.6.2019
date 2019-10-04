
#include "RGB_led_cnf.h"

#include "index.h"
ESP8266WebServer server(80);
//function for controlling the red LED
void redFunction()
{
	int value1 = server.arg("state1").toInt();
	value1 = map(value1, 0, 100, 0, 1023);

	if (value1 == 0)
		digitalWrite(red, LOW);//turn of the led
	else
		analogWrite(red, value1);//change the brightness of red

	server.send(200, "text/html", "red");
}

//function for controlling the green LED
void greenFunction()
{
	int value2 = server.arg("state2").toInt();
	value2 = map(value2, 0, 100, 0, 1023);

	if (value2 == 0)
		digitalWrite(green, LOW);//turn of the led
	else
		analogWrite(green, value2);//change the brightness of green

	server.send(200, "text/html", "green");
}

//function for controlling the blue LED
void blueFunction()
{
	int value3 = server.arg("state3").toInt();
	value3 = map(value3, 0, 100, 0, 1023);

	if (value3 == 0)
		digitalWrite(blue, LOW);//turn of the led
	else
		analogWrite(blue, value3);//change the brightness of blue

	server.send(200, "text/html", "blue");
}