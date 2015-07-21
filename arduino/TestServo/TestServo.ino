#include <Servo.h>
 
Servo servo;
int pos = 0;
 
void setup()
{
 servo.attach(9);
 servo.write(0);
}

void loop()
{
 for(pos = 0; pos<180; pos++){
 servo.write(pos);
 delay(15);
 }
 for(pos = 180; pos>0; pos--){
 servo.write(pos);
 delay(15);
 }
}
