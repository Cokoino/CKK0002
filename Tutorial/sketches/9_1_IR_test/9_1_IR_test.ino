/*****************************************************
 
 * This code applies to cokoino smart robot car kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0002
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#include <IRremote.h>
int RECV_PIN = 3; //define input pin 
IRsend irsend;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();  // Initialize the infrared receiver
}

void loop() 
{
 
 if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);//print the value in HEX format
    delay(50);
    irrecv.resume(); // Receive the next value
    delay(10);
  }
 
}
