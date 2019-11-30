#include "Handle_Web.h"
#include "Timer.h"
void setup() 
{

  //call the two functions used to connect connect to wifi
  //and setup the server
  //ESP.wdtDisable();
  DriversInit();
  connectToWiFi();
  setupServer();
  InitTimer1();
}

void loop()
{
 //the method below is used to manage the incoming request
//from the user
HandleWebClient();
}
