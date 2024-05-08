/*****************************************************
 
 * This code applies to cokoino smart robot car kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0002
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
/****************************************************
samrt robot car
              __
-------------|  |-----------------
-------------|  |-----------------
        M1 (------) M4
****************************************************/
#include <SCoop.h> //Import multithread library
#include <Adafruit_PWMServoDriver.h> //Import PWM library 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define WS2812_PIN 6   //WS2812 PIN
#define WS2812_COUNT 12  // How many NeoPixels are attached to the Arduino?
#define BRIGHTNESS 10  // NeoPixel brightness, 0 (min) to 255 (max)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(WS2812_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);

#define Buzz 11     //buzzer PIN
#define led_R 9
#define led_L 5

#define Line_L A0   //left PIN
#define Line_M A1   //middle PIN
#define Line_R A2   //right PIN

defineTask(TaskOne);    // Create subthread 1
defineTask(TaskTwo);    // Create subthread 2

///////////////////////////////////////////////////////////////////////////////////
void TaskOne::setup()   //Thread 1 setup
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); 
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0); 
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("HELLO WORLD!");
  lcd.setCursor(1,1);
  lcd.print("HELLO COKOINO!");
  
  pinMode(Line_L, INPUT_PULLUP);
  pinMode(Line_M, INPUT_PULLUP);
  pinMode(Line_R, INPUT_PULLUP);
}
void TaskTwo::setup(){  // Thread 2 setup
  pinMode(led_R, OUTPUT);
  pinMode(led_L, OUTPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
}

void setup(){
  mySCoop.start();//start setup
}
///////////////////////////////////////////////////////////////////////////////////
void TaskOne::loop() // loop subthread 1
{
  u8 trackingSensorVal = 0;
  trackingSensorVal = getTrackingSensorVal(); //get sensor value

  switch (trackingSensorVal)
  {
    case 0:   //000
      backward();//backward
      delay(15);
      break;
    case 7:   //111
      forward(); //car forward
      break;
    case 1:   //001
      turnRight(); //car turn Right
      delay(120);
      break;
    case 3:   //011
      turnRight(); //car turn Right  
      delay(120);
      break;
    case 2:   //010
    case 5:   //101
    case 6:   //110
      turnLeft(); //car turn left   
      delay(120);
      break;
    case 4:   //100
      turnLeft(); //car turn left
      delay(120);
      break;
    default:
      break;
  }
}

//when black line on one side is detected, the value of the side will be 0, or the value is 1
u8 getTrackingSensorVal() {
  u8 trackingSensorVal = 0;
  trackingSensorVal = (digitalRead(Line_L) == 1 ? 1 : 0) << 2 | (digitalRead(Line_M) == 1 ? 1 : 0) << 1 | (digitalRead(Line_R) == 1 ? 1 : 0) << 0;
  return trackingSensorVal;
}

void forward()
{
 pwm.setPWM(2, 0, -800);
 pwm.setPWM(3, 0, 800);
 pwm.setPWM(4, 0, 800);
 pwm.setPWM(5, 0, -800);
}

void backward()
{
 pwm.setPWM(2, 0, 850);
 pwm.setPWM(3, 0, -850);
 pwm.setPWM(4, 0, -850);
 pwm.setPWM(5, 0, 850);
}

void turnRight()
{
 pwm.setPWM(2, 0, -1400);
 pwm.setPWM(3, 0, 1400);
 pwm.setPWM(4, 0, 800);
 pwm.setPWM(5, 0, -800);
}

void turnLeft()
{
 pwm.setPWM(2, 0, -800);
 pwm.setPWM(3, 0, 800);
 pwm.setPWM(4, 0, 1400);
 pwm.setPWM(5, 0, -1400);
}

void Stopcar()
{
 pwm.setPWM(2, 0, 0);
 pwm.setPWM(3, 0, 0);
 pwm.setPWM(4, 0, 0);
 pwm.setPWM(5, 0, 0);
}


void TaskTwo::loop() // loop subthread 2
{ 
  digitalWrite(led_R,HIGH);
  digitalWrite(led_L,HIGH);
  colorWipe(strip.Color(255, 0, 0), 10); // Red
  delay(800);
  colorWipe(strip.Color(255, 150, 0), 10); // yellow
  delay(800);
  colorWipe(strip.Color(0, 255, 0), 10); // Green
  delay(800);
  colorWipe(strip.Color(0, 255, 255), 10); // CYAN
  delay(800);
  colorWipe(strip.Color(0, 0, 255), 10); // Blue
  delay(800);
  colorWipe(strip.Color(180, 0, 255), 10); // purple
  delay(800);
  colorWipe(strip.Color(127, 127, 127), 10); // White
  delay(800);
  colorWipe(strip.Color(0, 0, 0), 30); // Clear
  Serial.println("OK");
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {// For each pixel in strip...
    strip.setPixelColor(i, c);                 //  Set pixel's color (in RAM)
    strip.show();                              //  Update strip to match
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void loop(){
  yield();//start multithread task
}
