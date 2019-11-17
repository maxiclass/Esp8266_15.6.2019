#include "Handle_Web.h"
#include "Control.h"
#include "MpuControl.h"
ESP8266WebServer server(80);

const char* ssid = "DIGI-JPyU";
const char* password = "Parola12";
const int frequency = 60;  //60hz
const int resolution = 8;
const int maxvalue = 254; //max value for pwm's
Servo servo1;                        //class for servo

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
	server.on("/Motor4Function", Motor4Function);
	server.on("/MoveServoFunction", MoveServoFunction);

	// server for MPU DATA
	server.on("/vSend_Mpu_Ax_to_web", vSend_Mpu_Ax_to_web);
	server.on("/vSend_Mpu_Ay_to_web", vSend_Mpu_Ay_to_web);
	server.on("/vSend_Mpu_Az_to_web", vSend_Mpu_Az_to_web);

	server.on("/vSend_Mpu_Gx_to_web", vSend_Mpu_Gx_to_web);
	server.on("/vSend_Mpu_Gy_to_web", vSend_Mpu_Gy_to_web);
	server.on("/vSend_Mpu_Gz_to_web", vSend_Mpu_Gz_to_web);

	server.on("/vSend_Mpu_Mx_to_web", vSend_Mpu_Gx_to_web);
	server.on("/vSend_Mpu_My_to_web", vSend_Mpu_Gy_to_web);
	server.on("/vSend_Mpu_Mz_to_web", vSend_Mpu_Gz_to_web);
	
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


void MoveServoFunction()
{
	//int	valueServo = server.arg("statusServo").toInt();	
	//servo1.write(valueServo);
}

//function for controlling the red LED
void redFunction()
{
	int value1 = server.arg("state1").toInt();
	value1 = map(value1, 0, 254, 0, 1023);
	if (value1 == 0)
		digitalWrite(red, LOW);//turn of the led
	else
		//ledcWrite(red, value1);
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


//function for controlling the blue LED
void Motor4Function()
{
	int statusMotor4 = server.arg("statusMotor4").toInt();
	statusMotor4 = map(statusMotor4, 0, 100, 0, 1023);

	if (statusMotor4 == 0)
		digitalWrite(Motor4PIN, LOW);//turn of the led
	else
		analogWrite(Motor4PIN, statusMotor4);//change the brightness of blue

	server.send(200, "text/html", "Motor4");
}



//functions for sending web data from MPU -> ACC

void vSend_Mpu_Ax_to_web()
{
		server.send(200, "text/plain", String(fGetMpuStrAx()));
}

 void vSend_Mpu_Ay_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrAy()));
 }

 void vSend_Mpu_Az_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrAz()));
 }

//functions for sending web data from MPU -> GYR
 void vSend_Mpu_Gx_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrGx()));
 }
 void vSend_Mpu_Gy_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrGy()));
 }
void vSend_Mpu_Gz_to_web()
	 {
	 server.send(200, "text/plain", String(fGetMpuStrGz()));
	 }

//functions for sending web data from MPU -> MAG
 void vSend_Mpu_Mx_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrMx()));
 }
 void vSend_Mpu_My_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrMy()));
 }
 void vSend_Mpu_Mz_to_web()
 {
	 server.send(200, "text/plain", String(fGetMpuStrMz()));
 }


volatile unsigned long next;

void DriversInit()

{
	vCustomizeMotorClass(); // Alocate Pins for each motor and also all the other important values
	vInitServoMotors(); // Init Servo Motors configuration

	//start the Serial communication at 115200 bits/s
	Serial.begin(115200);

	vInit_Mpu(); // Init MPU sensors (accelerometer / gyroscope / magnetometer)

	//wait 1 s until the Serial communication is started
	delay(1000);
}


// initialize timer1 
void InitTimer1()
{
	noInterrupts();
	timer0_isr_init();
	timer0_attachInterrupt(ScheduleTime1);
	timer0_write(ESP.getCycleCount() + 160000); //160Mhz -> 160*10^6 = 1 second (160000000)
	interrupts();

}

void ScheduleTime1()
{
	// Set-up the next interrupt cycle
	timer0_write(ESP.getCycleCount() + 160000); //160Mhz -> 160*10^6 = 1 second (160000000)

	u32milisecondsCounter++;

	vSystemDroneControl();

	//activate 1 second interruput
	if ((u32milisecondsCounter % 1000) == 0)
	{

		//value = map(value, 0, 1024, 0, 180);
		//servo1.write(value);
		//Serial.println(servo1.read());
		//Serial.println(u32milisecondsCounter);
		vDoIsr1Sec();

		vprint_Mpu_data();

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