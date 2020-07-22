#include <Servo.h>
#include <NewPing.h>
#include "AFMotor.h"

#define TRIG_PIN  A5
#define ECHO_PIN  A4 

#define max_speed 150

boolean goesForward=false;
int distance;
long duration;

Servo myservo;

AF_DCMotor motor1(4); 
AF_DCMotor motor2(3);

 void moveBackward()
  {
    goesForward=false;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.setSpeed(max_speed);
    motor2.setSpeed(max_speed);
    delay(5);
  }

  void turnRight()
  {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);     
    delay(300);
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
  } 
  
  void turnLeft()
  {
    motor1.run(BACKWARD);     
    motor2.run(FORWARD);     
    delay(300);
    motor1.run(FORWARD);     
    motor2.run(FORWARD);
  }  

//===============================================================================
//  Initialization
//===============================================================================
void setup() {

pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
Serial.begin(9600);
myservo.attach(10);
myservo.write(90);

}


//===============================================================================
//  Main
//=============================================================================== 

void loop()
{

const int distance_object=20;
int distanceR = 0;
int distanceL = 0;

  // put your main code here, to run repeatedly:
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(ECHO_PIN, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

  moveForward();
  if(distance <= distance_object)
  {
    moveStop();
    delay(200);
    moveBackward();
    delay(200);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
     delay(200);
    
    if(distanceL<=distanceR)
    {
    turnLeft();
    moveStop();
    moveForward();
    }
      else
      {
        turnRight();
        moveStop();
        moveForward();
      }
  }

}
 

 void moveStop()
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE); 
  }

  void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
    delay(100);
    motor1.setSpeed(max_speed);
    motor2.setSpeed(max_speed);
    delay(5);
   }
 }

 int lookRight()
{
    myservo.write(90); 
    delay(500);
    int distance_R = distance;
    delay(100);
    myservo.write(140); 
    return distance_R;
}

int lookLeft()
{
    myservo.write(40); 
    delay(500);
    int distance_L = distance;
    delay(100);
    myservo.write(90); 
    return distance_L;
    delay(100);
}
