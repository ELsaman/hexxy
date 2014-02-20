
#include "SegmentServo.h"
#include <ServoNew.h>
Servo myservo; 

void setup()
{
    myservo.attach(12);

}

void loop()
{

    myservo.write(170,1.0f);
    delay(1000);
    myservo.write(50, 10.0f);
    delay(1000);

  /* add main program code here */

}
