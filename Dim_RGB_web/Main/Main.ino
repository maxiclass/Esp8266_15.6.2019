
#include "Handle_Web.h"

void setup() 
{

  //call the two functions used to connect connect to wifi
  //and setup the server
  connectToWiFi();
  setupServer();
  DriversInit();
  InitTimer1();
}

void loop()
{
 //the method below is used to manage the incoming request
//from the user
HandleWebClient();
}
