#include <digiServo.h>

digiServo servo = digiServo(2, 3, 4, 5);
int count = 0;
double prv = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {


  servo.angle(180);

  servo.track();

  
}
