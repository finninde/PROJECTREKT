#include <PLab_ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <ZumoReflectanceSensorArray.h>
#include <SoftwareServo.h>

#define LED 13

// Ultra sound
#define triggerPin 1
#define echoPin 2
#define servoPin 6

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1800 // 
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms

// Zumo motor
PLab_ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

#define aggressive 1
#define defensive 2
#define search 3

// See arduino servo example for using servo
SoftwareServo USServo;

//Sensor struct, contains all sensory input
struct Sensors{
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

int runForwardUntilEdge(int timeMillis){
  /* Give function time in millis you want the zumobot to run forward
   * Function runs until complete unless one of the following:
   * -1 something is to the left, i turned right
   * -2 something is to the right, i turned left
   */
  unsigned long startTime = millis();
  unsigned long endTime = startTime + timeMillis;
  while (startTime < endTime){
  if (sensor_values[0] > QTR_THRESHOLD){
    // if edge is left of me
    // GET ME AWAYYY
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    // return result
    return -1;
    }
  else if (sensor_values[5] > QTR_THRESHOLD){
    // if edge is right of me
    // GET ME AWAYY
     motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    // return result
    return -2; 
    }
  else {
    // Run forward
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    }
  }
  return 1;
  }

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
  float distance;
  while(!found  || angle==180){
    USServo.write(angle);
    distance = readUSSensor(2);
    if (distance < 0.1){
      found = true;
      return (angle - 90);}
    angle += 2;
    //Serial.print("Angle:");
    //Serial.println(angle);
  }
  return 666;
}

void setup() {
  //TODO: initialize sensors by running update
  sensors.init();
  button.waitForButton();
  updateAllSensors();
  USServo.attach(servoPin);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  int cool = findStuff();
  //Serial.print("====== WE COOOL ======:");
  //Serial.println(cool);

  Sensors sensor;
  sensor.UVLeft = 0;
  sensor.UVRight = 0;
  sensor.GyroX = 0;
  sensor.GyroY = 0;
  sensor.GyroZ = 0;
  
  //Update sensors like they should be
  updateAllSensors();
  //Evaluate and decide on a behavior
  int behavior = evaluate();
  // set a runtime for selected behavior
  int runtime = random(0,2);
  // run the behavior
  if (runBehavior(behavior, runtime)){
      // behavior ran and terminated

    }
  else{
      // behavior ran and should not be run again
      
    }  
  attack();
}

void attack() {
 /*
  while (true) {
    int angle = findStuff();
    
    if (abs(angle) < 5) {
      motors.forward(100, 10);
    }
    else {
      if (angle < 0) {
        motors.turnRight(100, -angle);
      }
      else {
        motors.turnLeft(100, angle);
      } 
    }
  }
  */
  motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  SoftwareServo::refresh(); // must refresh servo when using this library
}

