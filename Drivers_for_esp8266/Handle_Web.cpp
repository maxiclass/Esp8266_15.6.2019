#include "Handle_Web.h"

ESP8266WebServer server(80);

const char* ssid = "DIGI-JPyU";
const char* password = "Parola12";


String page = MAIN_page; //Read HTML contents
//the htmlIndex() is called everytime somebody access the address
//of the board in the browser and sends back a message.
void htmlIndex()
{
	//send the message to the user
	server.send(200, "text/html", page);
}

//connectToWiFi() is used to connect to the WiFi network
//using the SSID and PASSWORD variables created at the
//beginning of the code
void connectToWiFi()
{
	Serial.println("Connecting to the WiFi");
	//set the WiFi mode to WiFi_STA
	//the WiFi_STA means that the board will act as a station,
	//similar to a smartphone or laptop
	WiFi.mode(WIFI_STA);

	//connect to the WiFi network using the ssid and password strings
	WiFi.begin(ssid, password);

	//below we check the status of the WiFi and wait until the
	//board is connected to the network
	Serial.println("Waiting for connection");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	digitalWrite(red, HIGH);//turn of the led
		Serial.print(".");
	}

	//when the board is successfully connected to the network,
	//display the IP assigned to it in the serial monitor.
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	//Turn led low after a successful connection 
	digitalWrite(red, LOW);//turn of the led
}

//setupServer() function is used to set up and organise
//the website
void setupServer()
{
	//the method "server.on()" is to call a function when
	//the user access the location
	//the default location is "/"
	server.on("/", htmlIndex);
	server.on("/redFunction", redFunction);
	server.on("/greenFunction", greenFunction);
	server.on("/blueFunction", blueFunction);
	// 
	 //start the server
	server.begin();

	//print in Serial Monitor that the HTTP server is started
	Serial.println("HTTP server started");
}

void HandleWebClient()
{

	//the method below is used to manage the incoming request
//from the user
	server.handleClient();
}


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

volatile unsigned long next;

void DriversInit()

{
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	pinMode(TrigerSensorHC, OUTPUT); // Sets the trigPin as an Output
	pinMode(EchoSensorHC, INPUT); // Sets the echoPin as an Input
	//start the Serial communication at 115200 bits/s
	Serial.begin(115200);

	//wait 1 s until the Serial communication is started
	delay(1000);
}

void SensorDetectionInteruput()
{
	digitalWrite(TrigerSensorHC, HIGH);
	delayMicroseconds(20);
	digitalWrite(TrigerSensorHC, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds
	durationSensorHC = pulseIn(EchoSensorHC, HIGH);
	// Calculating the distance
	distanceSensorHC = (durationSensorHC * 0.034) / 2;

	
	SetDistanceLight(distanceSensorHC);

}

//set distance light compare with the sensor result
void SetDistanceLight(float distance)
{
	static int u32counter=0;
	u32counter++;
	if (u32counter >= 1000)
	{
		u32counter = 0;
		if (distance < 30.0)
		{
			digitalWrite(red, HIGH);//change the brightness of red
			digitalWrite(blue, LOW);//change the brightness of red
			digitalWrite(green, LOW);//change the brightness of red
		}
		if ((distance > 30.0) && (distance < 50.0))
		{
			digitalWrite(red, LOW);//change the brightness of red
			digitalWrite(blue, HIGH);//change the brightness of red
			digitalWrite(green, LOW);//change the brightness of reds of red
		}
		if ((distance > 50.0) && (HIGH < 150.0))
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
	Serial.println(distanceSensorHC);
	Serial.println(u32secondsCounter);
	//Serial.println(u32counter);

}

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
	u32milisecondsCounter++;
	if ((u32milisecondsCounter % 1000) == 0)
	{
		u32secondsCounter++;
		if ((u32secondsCounter % 60) == 0)
		{
			u32minutesCounter++;
		}
	}

	SensorDetectionInteruput();
	// Set-up the next interrupt cycle
	timer0_write(ESP.getCycleCount() + 1600000); //160Mhz -> 160*10^6 = 1 second (160000000)
}

