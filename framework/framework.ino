#define aggressive 1
#define defensive 2
#define search 3
#include <Servo.h>
// See arduino servo example for using servo
Servo USServo;
//Sensor struct, contains all sensory input
struct sensors{
  float UVLeft;
  float UVRight;
  float GyroX;
  float GyroY;
  float GyroZ;
  }

//behavior struct, add points towards a behavior
struct behaviors{
  int Agressive;
  int Defensive;
  int Search;
  }

void updateAllSensors(){
  //Updates all sensors in sensors struct
  }

int evaluate(){
  // Iterates sensors and returns a behavior it takes aggressive, 
  // defensive or search as arguments
  
  }

int runBehavior(behavior, runtime){
  // Runs a behavior for a runtime
  // Returns 1 if successfull and 0 if interrupted
  return 1;
  }

void setup() {
  //TODO: initialize sensors by running update
  updateAllSensors();
  USServo.attach(6);
}

void loop() {
  //Update sensors like they should be
  // finn is a d**k
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
