#include <ESP8266WiFi.h> // libarary as we are using NodeMCU/ESP8266
#include <ArduinoJson.h>


const char* ssid = "HotspotA5"; // Your WiFi name
const char* password = "12345678";   // Your WiFi password

WiFiClient client;
char servername[] = "api.openweathermap.org";
String result;

void setup() {
	Serial.begin(115200);
	Serial.println("Connecting");
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) { // the system will not progress until a connection is present 
											 // once connected it outputs the message connected 

		delay(500);
	}
	Serial.println("Connected");
	delay(500);



	if (client.connect(servername, 80)) { // starts client connection, checks for connection

	 // Note  please put your API_KEY after : &appid=<YOUR KEY>; see the exepmles below

	 //client.println("GET /data/2.5/weather?q=London,uk&appid=c04a103f23078b8f65c79d76829d71de");//By city name
	 //client.println("GET /data/2.5/weather?id=2172797&appid=c04a103f23078b8f65c79d76829d71de");// By city ID
	 //client.println("GET /data/2.5/weather?zip=94040,us&appid=c04a103f23078b8f65c79d76829d71de");//By zip code

	 // This is for myHouse, you must change the coordination to your location
		client.println("GET /data/2.5/weather?lat=35.766955&lon=10.8152621&appid=c04a103f23078b8f65c79d76829d71de");// By geographic code
		client.println("Host: api.openweathermap.org");
		client.println("User-Agent:ArduinoWiFi/1.1");
		client.println("Connection: close");
		client.println();
	}
	else {
		Serial.println("connection failed");
		Serial.println();
	}
	while (client.connected() && !client.available()) delay(1);
	while (client.connected() || client.available()) {
		char c = client.read();
		result = result + c;
	}
	client.stop();

	result.replace('[', ' ');
	result.replace(']', ' ');
	Serial.println(result);

	char jsonArray[result.length() + 1];
	result.toCharArray(jsonArray, sizeof(jsonArray));
	jsonArray[result.length() + 1] = '\0';

	StaticJsonBuffer<1024> json_buf;
	JsonObject &root = json_buf.parseObject(jsonArray);
	if (!root.success())
	{
		Serial.println("parseObject() failed");
	}

	String city = root["name"];
	float temp = root["main"]["temp"];
	String stateWeather = root["weather"]["main"];
	String countr = root["sys"]["country"];
	Serial.println();
	Serial.println("--------------------------------------------");
	Serial.print("The weather is :");
	Serial.println(stateWeather);
	Serial.print("The tempreture in ");
	Serial.print(city);
	Serial.print(" is ");
	Serial.print(temp - 273.15); // conersion to celsius 
	Serial.println(" degress celsius");
	Serial.println(city + " city is in " + countr);
}
void loop() { }

