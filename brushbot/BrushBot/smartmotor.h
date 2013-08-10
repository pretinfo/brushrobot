/**
 * @file smartmotor.h
 * @brief smart Motor
 * @author pretinfo
 */
 #ifndef SMARTMOTOR_h
 #define SMARTMOTOR_h
 

#include "l298n_motor_driver.h"
#include "gy271_compass.h"

#define LOGGING
#include "logging.h"

#define CLOCKWISE 1
#define COUNTERCLOCK 0
#define CORRECTSTEP 10

namespace BrushBot
{
    class SmartMotor 
  {
  	private:
		int leftspeed,rightspeed,curspeed;
		PowerMotor motor;
		int lastdiff;
		int diffspeed;////value = rightspeed - leftspeed; if>0 we need to lower rightspeed; if < 0  re need to lower leftspeed
  	public:
        /*
         * @brief Class constructor.
         * @param 
         */

	SmartMotor()
	{
	lastdiff = 0;
	leftspeed=0;
	rightspeed=0;
	curspeed =0;
		
	}
          
        void setSpeed(int speed)
        {
          	leftspeed = speed;
          	rightspeed = speed;
			curspeed = speed;
			//leftmotor.setSpeed(speed*3/4);//here wo can set the leftmoto's speed to 3/4 of right,because the dif of the to motor.
									//right is lower than left
			motor.setSpeed(speed);
        }
        
		
		void turn(char direction)
		{
			if(direction)
				{
					motor.setLeftSpeed(curspeed);
					motor.setRightSpeed(-curspeed);
				}
			else{
					motor.setLeftSpeed(-curspeed);
					motor.setRightSpeed(curspeed);
				}
		
		}
		
        int getLeftSpeed() const
        {
            return leftspeed;
        }
		int getDiffSpeed(){
			return diffspeed;			
			}
		void stepDiffSpeed(int step){
			diffspeed = diffspeed+step;//step is :+2 or -2
			if(step>0) motor.setRightSpeed(255-diffspeed);
			else motor.setLeftSpeed(255+diffspeed);
			}
		

		void correctBearing(int diff){					
			if((lastdiff*diff)<=0){
				INFO1("Good News --- correct bearing.........done!!!\n");
				if(	diffspeed<0) {
					motor.setLeftSpeed(255+diffspeed);//minus 
					leftspeed = 255+diffspeed;
					motor.setRightSpeed(255);
					rightspeed = 255;
				}
				else{
					motor.setLeftSpeed(255);
					leftspeed = 255;
					motor.setRightSpeed(255-diffspeed);	
					rightspeed = 255-diffspeed;
					}
				INFO("WITH A DIFFSPEED:%d",diffspeed);
				}

				if(diff>0){						
					leftspeed = leftspeed+CORRECTSTEP;	
					leftspeed = min(leftspeed,255);					
					motor.setLeftSpeed(leftspeed);					

					rightspeed = rightspeed-CORRECTSTEP;	
					rightspeed = max(rightspeed,-255);
					motor.setRightSpeed(rightspeed);	

					INFO("1-LEFtSPEED:%d,RIGHTSPEED,%d",leftspeed,rightspeed);
				}
				if(diff<0){
					leftspeed = leftspeed-CORRECTSTEP;	
					leftspeed = max(leftspeed,-255);
					motor.setLeftSpeed(leftspeed);

					rightspeed = rightspeed+CORRECTSTEP;	
					rightspeed = min(rightspeed,255);
					motor.setRightSpeed(rightspeed);

					INFO("2-LEFTSPEED:%d,RIGHTSPEED,%d",leftspeed,rightspeed);

				}
				delay(50);
		lastdiff = diff;
			}


        
    };
};
#endif
