#include<Servo.h>
#include <Wire.h>                 //IIC通讯库文件
#include <LiquidCrystal_I2C.h>    //1602屏IIC通信库文件
LiquidCrystal_I2C lcd(0x27,16,2); //实例化一个LCD类，地址为0x27
Servo myservo;  // 实例化一个舵机类

#define INT_A 4 //定义控制左电机转向的引脚 D4
#define INT_B 2 //定义控制右电机转向的引脚 D2
#define left_A 6 //定义控制左电机的转速（PWM）的引脚 D6
#define right_B 5 //定义控制右电机的转速（PWM）D5
#define buzzer A2 //定义蜂鸣器控制引脚为A2
#define Echo 13       //定义超声波接收脉冲宽度引脚
#define Trigger 12    //定义超声波触发引脚
#define distance_minimum 25
float distance,distance_10,distance_170;
int Speed_FB=150;
int Speed_LR=80;
int randNumber=0;
void setup() 
{
  Serial.begin(9600);     //设定串口波特率为9600
  delay(100);              //延时100ms
  pinMode(INT_A,OUTPUT);   //设定控制电机的引脚都为输出状态
  pinMode(INT_B,OUTPUT);
  pinMode(left_A,OUTPUT);
  pinMode(right_B,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(Trigger,OUTPUT);

  myservo.attach(11); //设定舵机控制引脚为D11
  myservo.write(90);  //初始化舵机为90度
  
  lcd.init();                      //初始化1602LCD屏            
  lcd.backlight();                 //关1602LCD屏背光
  lcd.setCursor(2,0);         //光标设定在第1行的第3个位置
  lcd.print("Hello world!");  //从第1行第3个位置开始显示“Hello world!”
  lcd.setCursor(0,1);         //光标设定在第2行的第1个位置
  lcd.print("COKOINO Arduino!"); //从第2行第1个位置开始显示“COKOINO Arduino!”
}
/////////////////////////////////////////////////////////
void loop() 
{
  ultrasonic_distance();
  //Serial.println(distance);
  if(distance>distance_minimum)
    {
    front();   //前进的函数（front()）
    }
  if(distance<=distance_minimum)
    {
    Stop();     //停止
    digitalWrite(buzzer,HIGH);
    delay(250);
    digitalWrite(buzzer,LOW);
    servo_wheel();
    if((distance_10<=distance_minimum)&&(distance_170<=distance_minimum))
      {back();delay(250);}
    if(distance_10<distance_170)
      {left();}
    if(distance_10>distance_170)
      {right();}
    if(distance_10==distance_170)
      {
      randNumber = random(1, 2);  //产生随机数
      if(randNumber==1)
        {left();}
      if(randNumber==2)
        {right();}
      }
    delay(250); 
    Stop();     //停止   
    }
}

///////////////////////////////////////////////////////////前进
void front()
{
  digitalWrite(INT_A,LOW);    //控制左电机正转
  digitalWrite(INT_B,HIGH);   //控制右电机正转
  analogWrite(left_A,Speed_FB);   //设定左右电机的速度（PWM=200)
  analogWrite(right_B,Speed_FB); 
}
///////////////////////////////////////////////////////////后退
void back()  
{
  digitalWrite(INT_A,HIGH);   //控制左电机反转
  digitalWrite(INT_B,LOW);    //控制右电机反转
  analogWrite(left_A,Speed_FB);   
  analogWrite(right_B,Speed_FB);
}
///////////////////////////////////////////////////////////左转
void left()
{
  digitalWrite(INT_A,LOW);     //控制左电机正转
  digitalWrite(INT_B,LOW);     //控制右电机反转
  analogWrite(left_A,Speed_LR);
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////右转
void right()
{
  digitalWrite(INT_A,HIGH);    //控制左电机反转
  digitalWrite(INT_B,HIGH);    //控制右电机正转
  analogWrite(left_A,Speed_LR);    //左右两电机的转速（PWM为100）
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////停止
void Stop()
{
  digitalWrite(INT_A,LOW);  
  digitalWrite(INT_B,LOW);
  analogWrite(left_A,0);    //左右两边的PWM都是0
  analogWrite(right_B,0);
}
///////////////////////////////////////////////////////////超声波测距
void ultrasonic_distance()
{
delay(100); 
digitalWrite(Trigger, HIGH);
delayMicroseconds(10);
digitalWrite(Trigger, LOW);
distance = pulseIn(Echo, HIGH) * 34 / 2000.0;
if(distance==0)
  distance=300;
delay(100);
}
///////////////////////////////////////////////////////////舵机转动
void servo_wheel()
{
myservo.write(10);
delay(150);
ultrasonic_distance();
distance_10=distance;
delay(150);
  
myservo.write(170);
delay(150);
ultrasonic_distance();
distance_170=distance;
delay(150);

myservo.write(90);
delay(300);
}
