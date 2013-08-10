
#ifndef GY271_COMPASS_h
#define GY271_COMPASS_h

#include <HMC5883L.H>
#include <Wire.h>

#include "l298n_motor_driver.h"

namespace BrushBot
{
class GYCompass{
	private:
		int bearing;
		float X_offset,Y_offset;
		HMC5883L compass;	// Store our compass as a variable.
		int error;		
		float X_max;  
		float X_min;  
		float Y_max;  
		float Y_min;  
		void getOffset(int i){
			
			Serial.print(i);
			Serial.print(":checking......");
			
			Serial.print("X_max:");
			Serial.print(X_max);
			Serial.print("X_min:");
			Serial.print(X_min);
			Serial.print("X_offset:");
			Serial.print(X_offset);

			Serial.print(",");
			
			Serial.print("Y_max:");
			Serial.print(Y_max);
			Serial.print("Y_min:");
			Serial.print(Y_min);
			Serial.print("Y_offset");			
			Serial.print(Y_offset);

			Serial.println(" ");


			// Retrive the raw values from the compass (not scaled).
			//MagnetometerRaw raw = compass.ReadRawAxis();
			// Retrived the scaled values from the compass (scaled to the configured scale).
			MagnetometerScaled scaled = compass.ReadScaledAxis();
			scaled = compass.ReadScaledAxis();
				if (  (abs(scaled.XAxis) < 500) && (abs(scaled.YAxis) < 500) && (abs(scaled.ZAxis) < 500)) //���ж����Һ���Ҫ���ܹ��˵��ܶ���ţ�����У׼�ľ��ȡ�
		        {  //���漸�о��Ƕ�ȡ��ÿ��������ֵ����Сֵ��Ȼ�������Ӧ��ƫ����
		            if(scaled.XAxis > X_max) {X_max = scaled.XAxis;}
		            if(scaled.YAxis > Y_max) {Y_max = scaled.YAxis;}
		 
		            if(scaled.XAxis < X_min) {X_min = scaled.XAxis;}
		            if(scaled.YAxis < Y_min) {Y_min = scaled.YAxis;}
		 
		            X_offset = (X_max + X_min) / 2.0;
		            Y_offset = (Y_max + Y_min) / 2.0;	
					}

			}
		// Output the data down the serial port.
		void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
			{
			  /* Serial.print("Raw:\t");
			   Serial.print(raw.XAxis);
			   Serial.print("   ");   
			   Serial.print(raw.YAxis);
			   Serial.print("   ");   
			   Serial.print(raw.ZAxis);
			   Serial.print("   \tScaled:\t");
			   
			   Serial.print(scaled.XAxis);
			   Serial.print("   ");   
			   Serial.print(scaled.YAxis);
			   Serial.print("   ");   
			   Serial.print(scaled.ZAxis);
			*/
			   Serial.print("   \tHeading:\t");
			   Serial.print(heading);
			   Serial.print(" Radians   \t");
			   Serial.print(headingDegrees);
			   Serial.println(" Degrees   \t");
			}
	public:
		GYCompass()
			{
			X_offset = 0.0;
			Y_offset = 0.0;
			error = 0;
			bearing = 0;
			X_max = 0.0;  
			X_min = 0.0;  
			Y_max = 0.0;  
			Y_min = 0.0;  			
			}
		void initialize()
			{
			  // Initialize the serial port.
			  Serial.begin(9600);
			  Serial.println("Starting the I2C interface.");
			  Wire.begin(); // Start the I2C interface.
			  Serial.println("Constructing new HMC5883L");
			  compass = HMC5883L(); // Construct a new HMC5883 compass.
			    
			  Serial.println("Setting scale to +/- 1.3 Ga");
			  error = compass.SetScale(1.3); // Set the scale of the compass.
			  if(error != 0) // If there is an error, print it out.
			    Serial.println(compass.GetErrorText(error));
			  
			  Serial.println("Setting measurement mode to continous.");
			  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
			  if(error != 0) // If there is an error, print it out.
			  Serial.println(compass.GetErrorText(error));		
			}
		
		void setOffset(float x, float y){
			X_offset = x;
			Y_offset = y;
			}
		void setBearing(int origin){
			bearing = origin;
			}
		int getBearing(){
			return bearing;
			}
		void checkOffset(int times){
			PowerMotor motor;				
			motor.setLeftSpeed(255);
			motor.setRightSpeed(-255);			
			int i = 0;
			while(i<times){
				i++;
				getOffset(i);
				delay(10);
				}
			/*
			motor.setLeftSpeed(-255);
			motor.setRightSpeed(255);
			while(i>0){
				i--;
				getOffset(i);
				delay(10);
				}
			*/
			motor.setLeftSpeed(0);
			motor.setRightSpeed(0);
			}
		float getDegree()
			{			
			MagnetometerRaw raw = compass.ReadRawAxis();
			MagnetometerScaled scaled = compass.ReadScaledAxis();		 
			// �����ʱ��ֱ�Ӽ���ƫ�����Ϳ�����		   
			float heading = atan2(scaled.YAxis - Y_offset, scaled.XAxis - X_offset);
			//float declinationAngle = 36.36/1000.0;  [�⼸���ǿ��Ǵ�ƫ�ǵģ�����������		
			//heading = heading + declinationAngle;    �ҵ��?������Ȼ�Է����ж��ô�����]		   
			if(heading < 0)	heading += 2*PI;		
			if(heading > 2*PI)	heading -= 2*PI;		 
			float headingDegrees = heading * 180/M_PI; 	
			
			// Output the data via the serial port.
			//Output(raw, scaled, heading, headingDegrees);
			// Normally we would delay the application by 66ms to allow the loop
			// to run at 15Hz (default bandwidth for the HMC5883L).
			// However since we have a long serial out (104ms at 9600) we will let
			// it run at its natural speed.
			//delay(30);
			return headingDegrees;
			}

};
};
#endif
