// MVP

/*
Drive forward and turn left or right when border is detected
  - Only reflectionsensor 0 and 5 are used.
*/
#include <PLab_ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewPing.h>
 
#define LED 13
 
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1500 // 
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     400 // 0 is stopped, 400 is full speed
#define TURN_SPEED        300
#define FORWARD_SPEED     400
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms

// Motor
PLab_ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

// Zumo sensors
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors;

// Ultra sound pins
const int echoPin = 3;
const int triggerPin = 2;
NewPing sonar(triggerPin, echoPin, maxDistance);

void setup()
{
   Serial.begin(9600);
   pinMode(LED,OUTPUT);
   
   sensors.init();
   button.waitForButton();
}

void loop()
{
  sensors.read(sensor_values);
  
  unsigned int time = sonar.ping();
  float distance =  sonar.convert_cm(time);

  if (distance == 0.0)
  {
    motors.turnRight(TURN_SPEED, 1);
  }
  else
  {
    if ((sensor_values[0] < QTR_THRESHOLD) || (sensor_values[5] < QTR_THRESHOLD))
    {
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      delay(200);
      return;
    }
    else
    {
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    }
  }
}

