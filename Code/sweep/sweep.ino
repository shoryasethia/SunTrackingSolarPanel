#include <Servo.h>

Servo myservo;  // Create a servo object

int pos = 0;    // Variable to store the servo position

void setup() {
  myservo.attach(9);  // Attach the servo to pin 9
}

void loop() {
  // // Sweep from 0 to 180 degrees
  // for (pos = 0; pos <= 180; pos += 1) {
  //   myservo.write(pos);         // Set servo position
  //   delay(15);                  // Wait for servo to reach the position
  // }

  // // Sweep from 180 to 0 degrees
  // for (pos = 180; pos >= 0; pos -= 1) {
  //   myservo.write(pos);         // Set servo position
  //   delay(15);                  // Wait for servo to reach the position
  // }
  // int pos = 0;    
  myservo.write(pos+90);  
  
}
