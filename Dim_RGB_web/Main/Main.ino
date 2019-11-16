#include "Handle_Web.h"



void setup() 
{

  //call the two functions used to connect connect to wifi
  //and setup the server
  DriversInit();
  connectToWiFi();
  setupServer();
  InitTimer1();
//  analogWriteFreq(60) ; // should give 60 Hz
}

void loop()
{
 //the method below is used to manage the incoming request
//from the user
HandleWebClient();
}
