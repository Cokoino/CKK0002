#include<Servo.h>
#include <Wire.h>                     //IIC library
#include <LiquidCrystal_I2C.h>     //1602LCD IIC library
LiquidCrystal_I2C lcd(0x27,16,2);  //insrantiate an LCD class，address 0x27
Servo myservo;                       // insrantiate a servo class
#include <IRremote.h>                 //IR library

#define INT_A 4       //Define pin 4 to control steering of left motor
#define INT_B 2       //Define pin 2 to control steering of right motor
#define left_A 6      //Define pin 6 to control the speed of left motor (PWM)
#define right_B 5     //Define pin 5 to control the speed of right motor (PWM)
#define buzzer A2     //The buzzer control pin is defined as A2
#define RGB_LED_L 12  //Define left eye LED lamp control pin as 12
#define RGB_LED_R 13  //Define right eye LED lamp control pin as 13
#define RECV_PIN A0   //The infrared control is defined as A0
bool buzzer_rings_flag=true;
bool RGB_LED_flag=true;
int Speed_FB=150;
int Speed_LR=80;
int servo_angle=90;

IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() 
{
  Serial.begin(9600);     //Set the serial port baud rate to 9600
  delay(100);              //delay 100ms
  pinMode(INT_A,OUTPUT);   //Set the pins of the control motor to the output state
  pinMode(INT_B,OUTPUT);
  pinMode(left_A,OUTPUT);
  pinMode(right_B,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(RGB_LED_L,OUTPUT);
  pinMode(RGB_LED_R,OUTPUT);

  myservo.attach(11);  //Set the steering gear control pin as 11
  myservo.write(90);   //Initialize the servo to 90 degrees
  irrecv.enableIRIn(); //Enable infrared reception
  
  lcd.init();                      //Initializes the 1602LCD screen          
  lcd.backlight();                 //Turn off the 1602LCD backlight
  lcd.setCursor(2,0);              //The cursor is set to the third position on line 1
  lcd.print("Hello world!");       //“Hello world!”is displayed from line 1, position 3
  lcd.setCursor(0,1);              //The cursor is set to the first position on line 2
  lcd.print("COKOINO Arduino!");   //“COKOINO Arduino!”is displayed from line 2, position 1
}
/////////////////////////////////////////////////////////
void loop() 
{
  if (irrecv.decode(&results)) 
  { 
  Serial.println(results.value, HEX); //Serial print data
  delay(50);
  irrecv.resume();
  }
  switch(results.value)    //Jump to the position of the corresponding value
  {
    case 0xff18e7 :  front(); results.value=0; break;        //Up button of remote control
    case 0xff4ab5 :  back();  results.value=0; break;        //down button of remote control
    case 0xff10ef :  left();  results.value=0; break;        //left button of remote control
    case 0xff5aa5 :  right(); results.value=0; break;        //right button of remote control
    case 0xff38c7 :  Stop();  results.value=0; break;        //OK button of remote control 
    case 0xffe01f :  buzzer_rings(); results.value=0;break;  //7 button of remote control
    case 0xff6897 :  servo_L(); results.value=0;break;       //* button of remote control
    case 0xffb04f :  servo_R(); results.value=0;break;       //# button of remote control
    case 0xff906f :  RGB_LED(); results.value=0;break;       //9 button of remote control
    default : break;
  }
}

///////////////////////////////////////////////////////////front
void front()
{
  digitalWrite(INT_A,LOW);        //Control left motor advance
  digitalWrite(INT_B,HIGH);       //Control right motor advance
  analogWrite(left_A,Speed_FB);   //Set the speed of the motor（PWM=200)
  analogWrite(right_B,Speed_FB); 
}
///////////////////////////////////////////////////////////back
void back()  
{
  digitalWrite(INT_A,HIGH);   //Control the left motor back
  digitalWrite(INT_B,LOW);    //Control the right motor back
  analogWrite(left_A,Speed_FB);   
  analogWrite(right_B,Speed_FB);
}
///////////////////////////////////////////////////////////turn left
void left()
{
  digitalWrite(INT_A,LOW);     //Control left motor advance
  digitalWrite(INT_B,LOW);     //Control the right motor back
  analogWrite(left_A,Speed_LR);
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////turn right
void right()
{
  digitalWrite(INT_A,HIGH);        //Control the left motor back
  digitalWrite(INT_B,HIGH);        //Control right motor advance
  analogWrite(left_A,Speed_LR);    //Set the speed of the motor（PWM=100）
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////stop
void Stop()
{
  digitalWrite(INT_A,LOW);  
  digitalWrite(INT_B,LOW);
  analogWrite(left_A,0);    //Set the speed of the motor（PWM=0）
  analogWrite(right_B,0);
}
///////////////////////////////////////////////////////////buzzer ring
void buzzer_rings()
{
 if(buzzer_rings_flag==true)
   {
   digitalWrite(buzzer,HIGH);
   buzzer_rings_flag=false;
   return; 
   }
 if(buzzer_rings_flag==false) 
   {
   digitalWrite(buzzer,LOW);
   buzzer_rings_flag=true;
   return;
   }
}
///////////////////////////////////////////////////////////servo turn left
void servo_L()
{
if(servo_angle<=130) 
  servo_angle+=40;
myservo.write(servo_angle);
}
///////////////////////////////////////////////////////////servo turn right
void servo_R()
{
if(servo_angle>=50) 
  servo_angle-=40; 
myservo.write(servo_angle); 
}
///////////////////////////////////////////////////////////RGB_LED
void RGB_LED()
{
 if(RGB_LED_flag==true)
   {
   digitalWrite(RGB_LED_L,HIGH);
   digitalWrite(RGB_LED_R,HIGH); 
   RGB_LED_flag=false;
   return;
   }
 if(RGB_LED_flag==false)
   {
   digitalWrite(RGB_LED_L,LOW);
   digitalWrite(RGB_LED_R,LOW);
   RGB_LED_flag=true;
   return; 
   }
}
