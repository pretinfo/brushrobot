/**
 * @file brushbot.h
 * @brief 
 * @author pretinfo
 */

#ifndef BRUSHBOT_h
#define BRUSHBOT_h

#include "smartmotor.h"
#include "cleanerhand.h"
#include "gy271_compass.h"
#include "newping_distance_sensor.h"
#include "moving_average.h"
#include "logging.h"

//******************state begin********************
#define START 0
#define CHECKINGDIFFSPEED 1
#define DIFFSPEEDCHECKED 2
#define WORKING 3
//******************state end*********************


#define TOO_CLOSE 25	//cm
#define MAX_DISTANCE TOO_CLOSE*30
#define DISTANCE_SENSOR_INIT 13,12,MAX_DISTANCE

#define COMPASSCHECKTIMES 10
#define SPEEDSTEP 20

namespace BrushBot
{
    class BrushBot
	{
	  	private:
			int robotID;
			int state;
			SmartMotor engine;
			CleanerHand brush;
			GYCompass compass;
			DistanceSensor distanceSensor;			
			MovingAverage<unsigned int, 3> distanceAverage;
			unsigned long lastcleantime;
			int lastdegree;
			boolean  symble;

	  	public:
			BrushBot():state(0){};
			BrushBot(int idnumber)
			{
				state = 0;
				robotID = idnumber;		
			}
			void initialize(){				
				compass.initialize();
				compass.checkOffset(COMPASSCHECKTIMES);
				int x = compass.getDegree();
				compass.setBearing(x);
				distanceSensor=DistanceSensor(DISTANCE_SENSOR_INIT);
				
				lastcleantime = 0;
				state = START;
				lastdegree = 0;
				symble = true;
				}
			
			unsigned long getLastCleanTime()
				{
					return lastcleantime;
				}

			void setLastCleanTime(unsigned long time)
				{
					lastcleantime = time;
				}
			
		    void cleanBrush()
			{
				INFO1("CLEANING...");
				brush.clean();			
				
			}	
			
			void Gogo(int speed, int bearing)
			{		
				if(state == DIFFSPEEDCHECKED)	
				{
					engine.setSpeed(speed);
					compass.setBearing(bearing);
					state = WORKING;
					INFO1(".....WORKING...NOW......");
					INFO("STATE:%d",state);
					}
			}
			
			void randomBearing()
			{	
				int curbearing = compass.getDegree();
				int randegree = random(45,135);
				curbearing = curbearing+randegree;
				curbearing = (curbearing>360)?curbearing-360:curbearing;
				compass.setBearing(curbearing);				
			
			}
			
			void checkDiffSpeed(){				
				
				if(state == START){					
					lastdegree=compass.getDegree();	
					engine.setSpeed(255);	
					delay(200);
					state = CHECKINGDIFFSPEED;
					INFO1("START TO CHECKING......OK!\n");
					}
				if(state == CHECKINGDIFFSPEED){
					INFO("DIFFSPEED:%d",engine.getDiffSpeed());
					int curdegree = compass.getDegree();

					//jump the line between 0 degree and 360 degree.we can't turn more than 90degree in 500ms
					if(abs(curdegree-lastdegree)>90) {
						lastdegree = curdegree;
						return;
						}
					if(curdegree>lastdegree){
						if(engine.getDiffSpeed()<0) state = DIFFSPEEDCHECKED;
						else engine.stepDiffSpeed(SPEEDSTEP);						
						
						}

					if(curdegree<lastdegree){
						if(engine.getDiffSpeed()>0) state = DIFFSPEEDCHECKED;
						else engine.stepDiffSpeed(-SPEEDSTEP);
						
						}
					
					  INFO("DIFFSPEED:%d",engine.getDiffSpeed());					
					  INFO("LASTDEGREE:%d",lastdegree);
					  INFO("CURDEGREE:%d",curdegree);

					lastdegree = curdegree;
					
					delay(200);

					}
				}
			
			void keepStraight(){
				if(state == WORKING){					
				int to = compass.getBearing();
				int from = compass.getDegree();
				INFO("bearing:%d",to);
				INFO("curdegree:%d",from);
				int diff = abs(from-to);
				int rotation = 0;
				if(diff < 180){
					if(from < to) rotation=-abs(from-to);
					if(from > to) rotation=abs(from-to);					
					}
				if(diff>180){
					if(from > to) rotation=-abs(360-(from-to));
					if(from < to) rotation=abs(360-(from-to));
					}	
				INFO("rotation(diff):%d",rotation);
				engine.correctBearing(rotation);	

				
					}
				}	
			
			void avoidObstacles(){
				if(state == WORKING){
					unsigned int distance = distanceAverage.add(distanceSensor.getDistance());				
					INFO("distance: %u\n", distance);			
	        		if (distance <= TOO_CLOSE) randomBearing();
					}
				}
			
			int getState()	{
				return state;
			}

    	};
};
#endif
