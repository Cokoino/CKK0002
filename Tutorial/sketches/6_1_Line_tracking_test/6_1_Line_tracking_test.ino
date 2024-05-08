/*****************************************************
 
 * This code applies to cokoino smart robot car kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0002
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#define Line_L A0   //Lfet Line Sensor PIN
#define Line_M A1   //Middle Line Sensor PIN
#define Line_R A2   //Right Line Sensor PIN

void setup()
{
  Serial.begin(9600);
  pinMode(Line_L, INPUT_PULLUP);
  pinMode(Line_M, INPUT_PULLUP);
  pinMode(Line_R, INPUT_PULLUP);
}

void loop()
{
  bool Left_Value = digitalRead(Line_L);
  bool Middle_Value = digitalRead(Line_M);
  bool Right_Value = digitalRead(Line_R);
  delay(200);
  Serial. print(String("Left=") + Left_Value +",");
  Serial. print(String("Middle=") + Middle_Value +",");
  Serial. println(String("Right=") + Right_Value);
    
}
