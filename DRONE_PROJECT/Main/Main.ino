#include "Handle_Web.h"
#include "Timer.h"
#include "Control.h"
#include "MpuControl.h"
#include "BMP_180.h"
void setup() 
{

  //call the two functions used to connect connect to wifi
  //and setup the server
  DriversInit();
  //connectToWiFi();
  //setupServer();

}

void loop()
{
 //the method below is used to manage the incoming request
//from the user
HandleWebClient();
delay(0);
      vMadgwickFilterControl();
delay(10);
      vProcess_BMP180_data();
delay(10);
}
