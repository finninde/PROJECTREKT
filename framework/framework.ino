#include <PLab_ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Servo.h>

// Macros for ultra sound
#define triggerPin 1
#define echoPin 2
#define servoPin 3

#define aggressive 1
#define defensive 2
#define search 3

// See arduino servo example for using servo
Servo USServo;
//Sensor struct, contains all sensory input
struct sensors{
  float UVLeft;
  float UVRight;
  float GyroX;
  float GyroY;
  float GyroZ;
  };

//behavior struct, add points towards a behavior
struct behaviors{
  int Agressive;
  int Defensive;
  int Search;
  };

void updateAllSensors(){
  //Updates all sensors in sensors struct
  }

int evaluate(){
  // Iterates sensors and returns a behavior it takes aggressive, 
  // defensive or search as arguments
  
  }

int runBehavior(int behavior, float runtime){
  // Runs a behavior for a runtime
  // Returns 1 if successfull and 0 if interrupted
  return 1;
  }

int findStuff (){
  bool found = false;
  int angle = 0;
  long duration;
  float distance;
  while(!found  || angle==180){
    USServo.write(angle);
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.00017;
    Serial.print("Distance:");
    Serial.println(distance);
    if (distance < 0.1){
      found = true;
      return angle;}
    angle += 2;
    Serial.print("Angle:");
    Serial.println(angle);
  }
  return -1;
}

void setup() {
  //TODO: initialize sensors by running update
  updateAllSensors();
  USServo.attach(servoPin);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  int cool = findStuff();
  Serial.print("====== WE COOOL ======:");
  Serial.println(cool);

  sensors sensor = {0, 0, 0, 0, 0};
  //Update sensors like they should be
  updateAllSensors();
  //Evaluate and decide on a behavior
  behavior = evaluate();
  // set a runtime for selected behavior
  runtime = random(0,2);
  // run the behavior
  if (runBehavior(behavior, runtime)){
      // behavior ran and terminated

    }
  else{
      // behavior ran and should not be run again
      
    }  
  
}
