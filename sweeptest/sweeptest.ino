/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <PLab_ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Servo.h>

#include <Servo.h>
const int triggerPin = 1;
const int echoPin = 2;

PLab_ZumoMotors motors;

Servo USServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

float readUSSensor(int len){
  float measurements[len];
  float arraySum = 0;
  float average;
  long duration;
  float distance;
  for (int i=0; i<len ; i++){
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.00017;
    measurements[i] = distance;
    }

   for (int i=0; i<len; i++){
      arraySum += measurements[i];
    }
  average = arraySum/len;
  return average;
  }

void setup() {
  USServo.attach(3);  // attaches the servo on pin 9 to the servo object
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}


int findStuff (){
  bool found = false;
  int angle = 0;
  float distance;
  while(!found  || angle==180){
    USServo.write(angle);
    distance = readUSSensor(2);
    if (distance < 0.1){
      found = true;
      return (angle - 90);}
    angle += 2;
    Serial.print("Angle:");
    Serial.println(angle);
  }
  return 666;
}

void attack()
{
 /*
  while (true)
  {
    int angle = findStuff();
    
    if (abs(angle) < 5)
    {
      motors.forward(100, 10);
    }
    else
    {
      
      if (angle < 0)
      {
        motors.turnRight(100, -angle);
      }
      else
      {
        motors.turnLeft(100, angle);
      }
      
    }
  }
  */

  runForwardUntilEdge(1000);
  
}

void loop() {
  int cool = findStuff();
  Serial.print("====== WE COOOL ======:");
  Serial.println(cool);
  attack();
}

