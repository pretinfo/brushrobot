#include <DCMotor.h>
#include <Stepper.h>
#include <HMC5883L.h>
#include <Wire.h>
#include <NewPing.h>

#include "brushbot.h"

BrushBot::BrushBot mybot;

unsigned long cleaninterval = 120000;//two minutes
unsigned long pasttime = 0;

void setup()
{
	mybot.initialize();
	Serial.println("setup.............oK");
}


void loop()
{  
  INFO("MILLIS:%ld",millis());
  INFO("LASTCLEANTIME:%ld",mybot.getLastCleanTime());
  
  //clean brush every 2 minutes
  pasttime = mybot.getLastCleanTime();
  pasttime = millis() - pasttime;
  if(pasttime > cleaninterval)  {
    	mybot.cleanBrush();
      	mybot.setLastCleanTime(millis());
  }

  //check the diff speed between the two wheels of the robot
  mybot.checkDiffSpeed();
  //the origine direction
  mybot.Gogo(255,270);
  //keep line to work
  mybot.keepStraight();
  mybot.avoidObstacles();      
}
