/*****************************************************
 
 * This code applies to cokoino smart robot car kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0002
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#define LED_R 9
#define LED_L 5
int PWM_data;
void setup() {
  pinMode(LED_R,OUTPUT);  
  pinMode(LED_L,OUTPUT);  
}
void loop() {
for(PWM_data=0;PWM_data<=255;PWM_data++){
  analogWrite(LED_R,PWM_data);  // PWM
  analogWrite(LED_L,PWM_data);  
  delay(10);  
  }  
for(PWM_data=255;PWM_data>=0;PWM_data--){
  analogWrite(LED_R,PWM_data); 
  analogWrite(LED_L,PWM_data);  
  delay(10); 
  }        
}
