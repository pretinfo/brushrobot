#include <Servo.h>
#include <st>
#define MAXLINE 8
int i = 0;
Servo eyeservo;  // 定义舵机对象，最多八个  
int pos = 0;    // 定义舵机转动位置

int servoctrl =9;
int i1=2,i2=4,i3=7,i4=8;
int i5=3,i6=5,i7=6,i8=9;
int motoplus=13, motominus=12, motoena=11;

union command
{
  struct velstruck
  {
     float  linear;
     float angular;
  } vel;     
  char data[MAXLINE];
}cmd;
int movspeed=0;
int rate=20;
char character = 'v';
boolean cmdok = false;

void recvcmd();
void servoround();
void stepmoto();
void excuteline();
void autocurtain();


int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read

int times = 0;
int back = 0;
boolean openable = true;
boolean backable = false;


int puls = 2;
int puls_ = 10;
/////////////////////////////////////////////////////////

void step5moto()
{
  int pulstime=1;
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, LOW);
  digitalWrite(i6, LOW);
  digitalWrite(i7, LOW);
  digitalWrite(i8, LOW);
  delay(pulstime);//1
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, LOW);
  digitalWrite(i6, LOW);
  digitalWrite(i7, LOW);
  digitalWrite(i8, LOW);
  delay(pulstime);//2
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, LOW);
  digitalWrite(i6, LOW);
  digitalWrite(i7, LOW);
  digitalWrite(i8, LOW);
  delay(pulstime);//3
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, HIGH);
  digitalWrite(i6, LOW);
  digitalWrite(i7, LOW);
  digitalWrite(i8, LOW);
  delay(pulstime);//4
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, HIGH);
  digitalWrite(i6, LOW);
  digitalWrite(i7, LOW);
  digitalWrite(i8, LOW);
  delay(pulstime);//5
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, HIGH);
  digitalWrite(i6, LOW);
  digitalWrite(i7, HIGH);
  digitalWrite(i8, LOW);
  delay(pulstime);//6
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, LOW);
  digitalWrite(i6, LOW);
  digitalWrite(i7, HIGH);
  digitalWrite(i8, LOW);
  delay(pulstime);//7
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);  
  digitalWrite(i5, LOW);
  digitalWrite(i6, LOW);
  digitalWrite(i7, HIGH);
  digitalWrite(i8, LOW);
  delay(pulstime);//8

}






void setup()
{
  //////
//  eyeservo.attach(servoctrl);  // 设置舵机控制针脚
  
  //////
  Serial.begin(9600); // 打开串口，设置波特率为9600 bps
  
  /////
  pinMode(i1, OUTPUT);      // sets the digital pin as output
  pinMode(i2, OUTPUT);      // sets the digital pin as output
  pinMode(i3, OUTPUT);      // sets the digital pin as output
  pinMode(i4, OUTPUT);      // sets the digital pin as output  
 
  pinMode(i5, OUTPUT);      // sets the digital pin as output
  pinMode(i6, OUTPUT);      // sets the digital pin as output
  pinMode(i7, OUTPUT);      // sets the digital pin as output
  pinMode(i8, OUTPUT);      // sets the digital pin as output  
  
//step5moto();
  
  /////
  //pinMode(motoena, OUTPUT);
//  pinMode(motoplus, OUTPUT);
//  pinMode(motominus, OUTPUT);  
  
  
}



void loop()
{
//  recvcmd();
//  servoround();  
// autocurtain();
//step5moto();
step5moto();
// delay(50000);
}
void autocurtain()
{
    val = analogRead(analogPin);    // read the input pin
    Serial.println(val);             // debug value
  
if(val>600) times = times +1;

if(val<200) back = back +1;

if(times>500)
{
   for(int i=0; i <= 5000; i++){
      
    //Serial.println(i);
     if(openable)  {
       //Serial.println("opening~");
       stepmoto();      
     }
   } 
 
//   delay(57600000);
//   delay(2000);
backable = true;
openable = false;
   times = 0;
}
if(back>500)
{
   for(int j=0; j <= 5000; j++){
       
     
      //Serial.println(j);
      if(backable) {
         stepmotorevers();      
         //Serial.println("backing~");
      }
   } 

//   delay(57600000);
//   delay(2000);
backable = false;
openable = true;
   back = 0;
}

// stepmotorevers(); 
 // excuteline();    
}

///////////////////////////////////////////////
void recvcmd()
{
   if (Serial.available() > 0) {
                // read the incoming byte:
                i = Serial.readBytesUntil(character, cmd.data, MAXLINE);
                Serial.println(i);
                if(MAXLINE == i) {
                  Serial.print(cmd.vel.linear) ;
                  Serial.print(cmd.vel.angular) ;
                  Serial.println("");
                  cmdok = true;
/*
Serial.print('-');
Serial.print(cmd.data[0]);                   Serial.print('-');
Serial.print(cmd.data[1]);                   Serial.print('-');
Serial.print(cmd.data[2]);                   Serial.print('-');
Serial.print(cmd.data[3]);                   Serial.print('-');
Serial.print(cmd.data[4]);                   Serial.print('-');
Serial.print(cmd.data[5]);                   Serial.print('-');
Serial.print(cmd.data[6]);                   Serial.print('-');
Serial.print(cmd.data[7]);                   Serial.print('-');
Serial.print(cmd.data[8]);                   Serial.print('-');
Serial.println("");
*/
                }
                else if(i == 0){
                  cmdok = false;
                //do nothing             
                }
                else {
                  cmdok = false;
                  //do nothing 
                  Serial.println("Error reading command!");
                }
   }
}
////////////////////////////////////////////////
void servoround()
{
      // 0到180旋转舵机，每次延时15毫秒
      for(pos = 0; pos < 180; pos += 30)  
     {
       eyeservo.write(pos);  
     }
      // 180到0旋转舵机，每次延时15毫秒 
     /* for(pos = 180; pos>=1; pos-=1)
      {                               
        eyeservo.write(pos);
        delay(15);
      }
      */
} 
//////////////////////////////////////////////
//FOUR LINE STEP
//////////////////////////////////////////////
void stepmoto()
{
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);
  
  delay(puls);
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  delay(puls);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  delay(puls);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);
  
  delay(puls);
 
  // Serial.println("one step!");
}

void stepmotorevers()
{
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);
  
  delay(puls_);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  delay(puls_);
  

  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  delay(puls_);
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
  delay(puls_);
 
  // Serial.println("one step!");
}

//////////////////////////////////
//
/////////////////////////////////
void excuteline()
{
  if(cmdok){
    movspeed = cmd.vel.linear; 
  Serial.print("movspeed:");
  Serial.println(movspeed);
    if(movspeed!= 0){    
      movspeed = rate*movspeed;
      if(movspeed > 0){
        digitalWrite(motoplus,HIGH);
        digitalWrite(motominus,LOW);
//        analogWrite(motoena,movspeed);        
        analogWrite(motoena,80+movspeed);        
      }
      else{
        digitalWrite(motoplus,LOW);
        digitalWrite(motominus,HIGH);
        movspeed = -movspeed;
        analogWrite(motoena,80+movspeed);        
      }
      delay(1000);
    }
  }
  
  movspeed = 0;
  digitalWrite(motoplus,LOW);
  digitalWrite(motominus,LOW);
  //analogWrite(motoena,0);
  

  
}
