/**
*filename cleanerhand.h 
*breif 
*author pretinfo
*todo add interface class
*need <stepper.h>
**/


#ifndef CLEANERHAND_h
#define CLEANERHAND_h

#include "smartmotor.h"

#define STEPSPERREVOLUTION 128// change this to fit the number of steps per revolution
			// for your motor

#define	MOTOR_PIN_1     8	
#define	MOTOR_PIN_2	9
#define	MOTOR_PIN_3	10
#define	MOTOR_PIN_4	11

#define MOTORSPEED 150

#define CLEANTIMES 3

namespace BrushBot
{
	class CleanerHand
		{
		private:			
			Stepper cleanStepper;			 //NOT SUER IF NEED TO DEFINE CONSTRUCTER OR NOT
			SmartMotor helppower;//for the out of the stepper is too small ,wo need the engine to help the stepper

		public:
			CleanerHand(){

				// initialize the stepper library on pins 8 through 11:		
				cleanStepper = Stepper(STEPSPERREVOLUTION,MOTOR_PIN_1,MOTOR_PIN_2,\
										MOTOR_PIN_3,MOTOR_PIN_4);
				
				//Stepper cleanStepper(STEPSPERREVOLUTION,MOTOR_PIN_1,MOTOR_PIN_2,\
					//					MOTOR_PIN_3,MOTOR_PIN_4);
				}

			void clean(){		
				int i = 0;
				
				cleanStepper.setSpeed(MOTORSPEED);
				// step 1/100 of a revolution:
				while(i<CLEANTIMES){
					i++;
//					cleanStepper.step(STEPSPERREVOLUTION*32);//128*32means 360 degree,one circle for 28byj48 ,8pai(a-ab-b-bc...)
					
					helppower.setSpeed(-255);
					cleanStepper.step(STEPSPERREVOLUTION*10);
					helppower.setSpeed(0);

					delay(1000);

					helppower.setSpeed(255);
					cleanStepper.step(-STEPSPERREVOLUTION*10);
					helppower.setSpeed(0);
					delay(1000);

					}
				}
		
		};
};

#endif
