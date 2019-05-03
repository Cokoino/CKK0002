#include<Servo.h>
#include <Wire.h>                    //IIC library file 
#include <LiquidCrystal_I2C.h>    //1602 IIC library file 
LiquidCrystal_I2C lcd(0x27,16,2); //Instantiate an LCD class at address 0x27
Servo myservo;  // Instantiate a servo motor class

#define INT_A 4 //Define control left motor steering as pin 4
#define INT_B 2 //Define control left motor steering as pin 2
#define left_A 6 //Define the control left motor speed as pin 6（PWM）
#define right_B 5 //Define the control left motor speed as pin 5（PWM）
#define buzzer A2 //Define pin A2 that controls the buzzer
#define RGB_LED_L 12  //Define left eye LED lights
#define RGB_LED_R 13  //Define right eye LED lights
bool buzzer_rings_flag=true;
bool RGB_LED_flag=true;
int Speed_FB=150;
int Speed_LR=80;
int servo_angle=90;
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

  myservo.attach(11); //Set the control servo motor as pin 11
  myservo.write(90);  //Initialize the servo motor to 90 degrees
  
  lcd.init();                    //Initializes the 1602LCD screen          
  lcd.backlight();               //Turn off the 1602LCD backlight
  lcd.setCursor(2,0);            //The cursor is set to the third position on line 1
  lcd.print("Hello world!");     //Display “Hello world!” from line 1, position 3
  lcd.setCursor(0,1);            //The cursor is set to the first position on line 2
  lcd.print("COKOINO Arduino!"); //Display “COKOINO Arduino!” from line 2,position 1
}
/////////////////////////////////////////////////////////
void loop() 
{ 
  char BT_data;    //Defines a variable to receive data read by bluetooth
  if(Serial.available())     //Determine whether data is received
  {
    BT_data = Serial.read();       //Read the received data and assign it to val
  }
  switch(BT_data)    //Determine the data and then execute the corresponding function
  {
    case 'U':  front();  break;    //advance
    case 'D':  back();   break;    //reverse
    case 'L':  left();   break;    //turn left
    case 'R':  right();  break;    //turn right
    case 'S':  Stop();   break;    //stop
    case '1':  buzzer_rings(); break;
    case '2':  servo_L(); break;
    case '3':  servo_R(); break;
    case '4':  RGB_LED(); break;
    default:break;
  }
}

///////////////////////////////////////////////////////////advance
void front()
{
  digitalWrite(INT_A,LOW);        //Control left motor forward rotation
  digitalWrite(INT_B,HIGH);       //Control right motor forward rotation
  analogWrite(left_A,Speed_FB);   //Set the speed of the motor（PWM=200)
  analogWrite(right_B,Speed_FB); 
}
///////////////////////////////////////////////////////////reverse
void back()  
{
  digitalWrite(INT_A,HIGH);   //Control left motor reverse
  digitalWrite(INT_B,LOW);    //Control right motor reverse
  analogWrite(left_A,Speed_FB);   
  analogWrite(right_B,Speed_FB);
}
///////////////////////////////////////////////////////////turn left
void left()
{
  digitalWrite(INT_A,LOW);       //Control left motor forward rotation
  digitalWrite(INT_B,LOW);       //Control right motor reverse
  analogWrite(left_A,Speed_LR);  //Set the speed of the motor（PWM为100）
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////turn right
void right()
{
  digitalWrite(INT_A,HIGH);        //Control left motor reverse
  digitalWrite(INT_B,HIGH);        //Control right motor forward rotation
  analogWrite(left_A,Speed_LR);    //Set the speed of the motor（PWM为100）
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////stop
void Stop()
{
  digitalWrite(INT_A,LOW);  
  digitalWrite(INT_B,LOW);
  analogWrite(left_A,0);    //Set the motor speed as 0
  analogWrite(right_B,0);
}
///////////////////////////////////////////////////////////Buzzer rang
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
///////////////////////////////////////////////////////////Servo motor left turn
void servo_L()
{
if(servo_angle<=130) 
  servo_angle+=40;
myservo.write(servo_angle);
}
///////////////////////////////////////////////////////////Servo motor right turn
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
