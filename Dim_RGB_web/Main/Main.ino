#include "ESP8266WebServer.h"
#include "RGB_led_cnf.h"
#include "index.h" //Our HTML webpage contents with javascripts

// ESP8266WebServer server(80);
extern const char* ssid = "DIGI-JPyU";
extern const char* password = "Parola12";




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

void setup() 
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

  //call the two functions used to connect connect to wifi
  //and setup the server
  connectToWiFi();
  setupServer();
  InitTimer1();
}

void loop()
{
  //the method below is used to manage the incoming request
  //from the user
  server.handleClient();
}
