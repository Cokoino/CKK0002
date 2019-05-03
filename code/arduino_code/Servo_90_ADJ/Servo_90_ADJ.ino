#include<Servo.h>
Servo myservo;  // 实例化一个舵机类

void setup() {  
myservo.attach(11); //设定舵机控制引脚为D11
myservo.write(90);  //初始化舵机为90度
delay(100);       //延时100ms 
}
/////////////////////////////////////////////////////////
void loop() {
 }
