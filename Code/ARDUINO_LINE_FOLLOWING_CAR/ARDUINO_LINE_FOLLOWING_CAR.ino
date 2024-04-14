//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define left A0
#define right A1

//defining motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);


const int n = 5;
float eff[n];
int i = 1;
int k=1;
int maxm=0;
int max_index=0;

// Define the pin for solar panel voltage input
const int solarPanelPin = A2;

float solarVoltage ()
 {
   // Read the solar panel voltage
    float voltage = analogRead(solarPanelPin);

   // Print the solar panel voltage value
    // Serial.print("Solar Panel Voltage: ");
    // Serial.println(voltage/255);

    return voltage/255;
 }

void record ()
 {
    if(i<=n)
     {
      eff[i] = solarVoltage();
      maxm=max(eff[i], maxm);
      i++;
      motor1.run(FORWARD);
      motor1.setSpeed(200);
      motor2.run(FORWARD);
      motor2.setSpeed(200);
      motor3.run(FORWARD);
      motor3.setSpeed(200);
      motor4.run(FORWARD);
      motor4.setSpeed(200);
      delay(200);

      if (i==n)
      {
        for(int j=0;j<n;j++)
         {
           if(maxm==eff[j])
            {
              max_index=j+1;

              break;
            }
         }
      }
     }

     
    
 }

void move()
 {
      if(k<max_index)
       {
        motor1.run(FORWARD);
        motor1.setSpeed(115);
        motor2.run(FORWARD);
        motor2.setSpeed(115);
        motor3.run(FORWARD);
        motor3.setSpeed(115);
        motor4.run(FORWARD);
        motor4.setSpeed(115);
        k++;
        delay(200);
       }

       if(k==max_index)
       {
        motor1.run(RELEASE);
        motor1.setSpeed(0);
        motor2.run(RELEASE);
        motor2.setSpeed(0);
        motor3.run(RELEASE);
        motor3.setSpeed(0);
        motor4.run(RELEASE);
        motor4.setSpeed(0);
      
       }
      
 }

void setup() {
  //declaring pin types
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  pinMode(solarPanelPin,INPUT);
  //pinMode(frequencyReceivePin, INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  int line;   // set it to 1 if line is black, and 0 if line is white
  line = 1;

  //printing values of the sensors to the serial monitor
  // Serial.println(digitalRead(left));
  
  // Serial.println(analogRead(right));

  //line not detected by both
  if(!digitalRead(left)==line && !digitalRead(right)==line){
    //Forward
    motor1.run(FORWARD);
    motor1.setSpeed(115);
    motor2.run(FORWARD);
    motor2.setSpeed(115);
    motor3.run(FORWARD);
    motor3.setSpeed(115);
    motor4.run(FORWARD);
    motor4.setSpeed(115);
  }
  //line detected by right sensor
  else if(!digitalRead(left)==line && digitalRead(right)==line){
    //turn right
    motor1.run(FORWARD);
    motor1.setSpeed(200);
    motor2.run(FORWARD);
    motor2.setSpeed(200);
    motor3.run(BACKWARD);
    motor3.setSpeed(200);
    motor4.run(BACKWARD);
    motor4.setSpeed(200);
    
  }
  //line detected by left sensor
  else if(digitalRead(left)==line && !digitalRead(right)==line){
    //turn left
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
  else if(digitalRead(left)==line && digitalRead(right)==line){
    //stop
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);

    if(i<=n)
     {
      record();
     }

    else if (i>n)
     {
      move();
     }
   
  }
  
}
