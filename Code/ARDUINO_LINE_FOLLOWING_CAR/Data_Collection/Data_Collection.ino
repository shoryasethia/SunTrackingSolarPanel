//ARDUINO LINE FOLLOWING CAR//
// YOU HAVE TO INSTALL THE AFMOTOR LIBRARY BEFORE UPLOAD THE CODE//
// GO TO SKETCH >> INCLUDE LIBRARY >> ADD .ZIP LIBRARY >> SELECT AF MOTOR ZIP FILE //
 
//including the libraries
#include <AFMotor.h>
#include<math.h>

//defining pins and variables
#define left A0
#define right A1

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

const int n = 10;
float eff[n];
int i = 1;
int maxm=0;
// Define the pin for solar panel voltage input
const int solarPanelPin = A4;

float solarVoltage ()
 {
   // Read the solar panel voltage
    float voltage = analogRead(solarPanelPin);

   // Print the solar panel voltage value
    Serial.print("Solar Panel Voltage: ");
    Serial.println(voltage/255);
    
    return voltage/255;
 }

float record ()
 {
    if(i<=n)
     {
      eff[i] = solarVoltage();

      
      maxm=max(eff[i], maxm);


      i++;
      motor1.run(FORWARD);
      motor1.setSpeed(150);
      motor2.run(FORWARD);
      motor2.setSpeed(150);
      motor3.run(FORWARD);
      motor3.setSpeed(150);
      motor4.run(FORWARD);
      motor4.setSpeed(150);
     }

     else if (i>n)
      {

      }
    
 }


//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);


void setup() {
  //declaring pin types
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  int line;   // set it to 0 if line is black, and 1 if line is white
  line = 0;

  //printing values of the sensors to the serial monitor
  Serial.println(digitalRead(left));
  
  Serial.println(digitalRead(right));

  //line detected by both
  if(digitalRead(left)==line && digitalRead(right)==line){
    //Forward
    motor1.run(FORWARD);
    motor1.setSpeed(75);
    motor2.run(FORWARD);
    motor2.setSpeed(75);
    motor3.run(FORWARD);
    motor3.setSpeed(75);
    motor4.run(FORWARD);
    motor4.setSpeed(75);
  }
  //line detected by left sensor
  else if(digitalRead(left)==line && !analogRead(right)==line){
    //turn left
    motor1.run(FORWARD);
    motor1.setSpeed(200);
    motor2.run(FORWARD);
    motor2.setSpeed(200);
    motor3.run(BACKWARD);
    motor3.setSpeed(200);
    motor4.run(BACKWARD);
    motor4.setSpeed(200);
    
  }
  //line detected by right sensor
  else if(!digitalRead(left)==line && digitalRead(right)==line){
    //turn right
    motor1.run(BACKWARD);
    motor1.setSpeed(200);
    motor2.run(BACKWARD);
    motor2.setSpeed(200);
    motor3.run(FORWARD);
    motor3.setSpeed(200);
    motor4.run(FORWARD);
    motor4.setSpeed(200);
   
  }
  //line detected by none
  else if(!digitalRead(left)==line && !digitalRead(right)==line){
    //stop
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);

    record();

   
  }
  
}
