#include "Handle_Web.h"
#include "Timer.h"
#include "Control.h"
#include "MpuControl.h"
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
     // vPrintEulerAngles();
delay(10);
}
