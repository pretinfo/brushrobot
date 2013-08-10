/**
 * @file l298n_motor_driver.h
 * @brief Motor device driver for the L298n motor shield.
 * @author pretinfo
 */
#ifndef L298N_MOTOR_DRIVER_H
#define L298N_MOTOR_DRIVER_H

#include <DCMotor.h>
#include "motor_driver.h"

#define LEFTMOTOR_PWM 3 
#define LEFTMOTOR_DPIN 4

#define RIGHTMOTOR_PWM 5
#define RIGHTMOTOR_DPIN 7


namespace BrushBot
{  
	class PowerMotor:public MotorDriver
{
      private:
       DCMotor leftmotor;//motor(3,4);is error,c++ not allow initialize here
       DCMotor rightmotor;//motor(3,4);is error,c++ not allow initialize here
       int currentSpeed;
	   int leftSpeed,rightSpeed;
	  public:


  /*
         * @brief Class constructor.
         * @param
         */
  
PowerMotor():MotorDriver()
  		{
	  		leftmotor= DCMotor(LEFTMOTOR_PWM, LEFTMOTOR_DPIN);
			rightmotor = DCMotor(RIGHTMOTOR_PWM, RIGHTMOTOR_DPIN);
			currentSpeed=0;
  		}


	void setLeftSpeed(int speed)
        {
            leftSpeed = speed;
            if (speed >= 0) {
                leftmotor.setSpeed(speed);
                leftmotor.run(FORWARD);
            }
            else {
                leftmotor.setSpeed(-speed);
                leftmotor.run(BACKWARD);
            }
        }

		void setRightSpeed(int speed)
        {
            rightSpeed = speed;
            if (speed >= 0) {
                rightmotor.setSpeed(speed);
                rightmotor.run(FORWARD);
            }
            else {
                rightmotor.setSpeed(-speed);
                rightmotor.run(BACKWARD);
            }
        }


		void setSpeed(int speed){
			leftSpeed = speed;
			rightSpeed = speed;
			currentSpeed = speed;
			setLeftSpeed(speed);
			setRightSpeed(speed);
			}

        int getSpeed() const
        {
            return currentSpeed;
        }


		};
};
#endif
