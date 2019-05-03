#include<Servo.h>
#include <Wire.h>                 //IIC通讯库文件
#include <LiquidCrystal_I2C.h>    //1602屏IIC通信库文件
LiquidCrystal_I2C lcd(0x27,16,2); //实例化一个LCD类，地址为0x27

#define INT_A 4 //定义控制左电机转向的引脚 D4
#define INT_B 2 //定义控制右电机转向的引脚 D2
#define left_A 6 //定义控制左电机的转速（PWM）的引脚 D6
#define right_B 5 //定义控制右电机的转速（PWM）D5
#define RGB_LED_L 12  //定义左眼LED灯
#define RGB_LED_R 13  //定义右眼LED灯

Servo myservo;  // 实例化一个舵机类

const int S1 = 9;  //控制右边循迹传感器的引脚为D9
const int S2 = 8;  //控制中间循迹传感器的引脚为D8
const int S3 = 7;  //控制左边循迹传感器的引脚为D7
int s1,s2,s3;   //定义3个变量，用于分别接收3个循迹传感器读取到的数字值（0或1）

int Speed_FB=90;
int Speed_LR=55;

void setup() 
{  
  Serial.begin(9600);    //设定串口监视器的波特率为9600
  delay(100);       //延时100ms
  pinMode(INT_A,OUTPUT);      //设定控制电机的引脚都为输出状态
  pinMode(INT_B,OUTPUT);
  pinMode(left_A,OUTPUT);
  pinMode(right_B,OUTPUT);
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(RGB_LED_L,OUTPUT);
  pinMode(RGB_LED_R,OUTPUT);
  digitalWrite(RGB_LED_L,HIGH);
  digitalWrite(RGB_LED_R,HIGH); 
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
    s1 = digitalRead(S1); //将S1，S2,S3引脚读取到的数字值赋给s1,s2,s3
    s2 = digitalRead(S2);
    s3 = digitalRead(S3);
    
    if(s2==1)  //如果s2引脚（中间那个）检测到黑线
    {
      if(s3==1 && s1==0)  //再判断，如果s3（左边那个）检测到黑线，s1没检测到
      {
        left(Speed_LR/2);     //那就向左转
      }
      else if(s3==0 && s1==1)  //如果s3没检测到，而s1检测到
      {
        right(Speed_LR/2);   //那就向右转
      }
      else      //其它情况
      {
        front(Speed_FB);   //那就前进
      }
    }
  
    else  //s2没检测到黑线
    {
      if(s3==1&&s1==0)  //如果s3检测到黑线
      {
        left(Speed_LR);     //向左转
      }
      else if(s3==0&&s1==1)  //s1检测到黑线
      {
        right(Speed_LR);    //向右转
      }
    } 
}
///////////////////////////////////////////////////////////前进
void front(int Speed)
{
  digitalWrite(INT_A,LOW);    //控制左电机正转
  digitalWrite(INT_B,HIGH);   //控制右电机正转
  analogWrite(left_A,Speed_FB);   //设定左右电机的速度（PWM=200)
  analogWrite(right_B,Speed_FB); 
}
///////////////////////////////////////////////////////////左转
void left(int Speed)
{
  digitalWrite(INT_A,HIGH);    //控制左电机反转
  digitalWrite(INT_B,HIGH);    //控制右电机正转
  analogWrite(left_A,Speed_LR);
  analogWrite(right_B,Speed_LR);
}
///////////////////////////////////////////////////////////右转
void right(int Speed)
{
  digitalWrite(INT_A,LOW);     //控制左电机正转
  digitalWrite(INT_B,LOW);     //控制右电机反转
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
