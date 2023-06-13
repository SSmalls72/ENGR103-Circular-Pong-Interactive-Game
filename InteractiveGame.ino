//Author: Sinjin Small
//ENGR 103 Final Game: Circular Pong
//PROF. Udell

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h> 

//Declaring Variables
int score = 0;
int buttonStatus;
int switchState;

//Declaring Timers
AsyncDelay delay_fastLightCycle;
AsyncDelay delay_slowLightCycle;


void setup() {
  // put your setup code here, to run once:
  //General Setup

  Serial.begin(9600);
  CircuitPlayground.begin();

  //Pin Setup
  pinMode(5, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLUP);

  //Timer Setup
  delay_fastLightCycle.start(2700, AsyncDelay::MILLIS);
  delay_slowLightCycle.start(4500, AsyncDelay::MILLIS);
}

void loop() {
  // put your main code here, to run repeatedly:

//Turn goal light on
  CircuitPlayground.setPixelColor(2, 0, 255, 0);
  
  
//Create direction variable 
  int direction;
  direction = score % 2;
  
//Use direction variable to determine the direction of light flow
  if(direction == 0) {
    lightRotateRight();
  }
  else {
    lightRotateLeft();
  }

//Read switch state and set to a variable
  switchState = digitalRead(7);

//Use switch state to determine speed of light
if (switchState) {
  if (delay_slowLightCycle.isExpired()) { 
     buttonStatus = digitalRead(5);
     if (buttonStatus){
       CircuitPlayground.playTone(1000, 100);
        score++;
     }
     else {
       CircuitPlayground.playTone(50, 100);
     }
     delay_slowLightCycle.repeat(); // Count from when the delay expired, not now
  }
}
else{
  if (delay_fastLightCycle.isExpired()) { 
      buttonStatus = digitalRead(5);
      if (buttonStatus){
        CircuitPlayground.playTone(1000, 100);
        score++;
      }
      else {
        CircuitPlayground.playTone(50, 100);
      }
      delay_fastLightCycle.repeat(); // Count from when the delay expired, not now
  }
}


//End game function 
if(score == 5) {
  CircuitPlayground.clearPixels();

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0);
    CircuitPlayground.playTone(100 * i, 100);
  }
}

Serial.print("Switch State:"); Serial.println(switchState);

}


//Function that triggers the light change
int lightChange(int lightNum, bool speed) {
  if(speed) {
  
    for(int i = 0; i < 255; i++){
      CircuitPlayground.setPixelColor(lightNum, i, i, i);
    }

  delay(50);
    for(int i = 255; i > 0; i--){
      CircuitPlayground.setPixelColor(lightNum, i, i, i);
    }
  delay(250);
  }
  else {
    for(int i = 0; i < 255; i++){
      CircuitPlayground.setPixelColor(lightNum, i, i, i);
    }
  delay(250);
    for(int i = 255; i > 0; i--){
      CircuitPlayground.setPixelColor(lightNum, i, i, i);
    }
  delay(250);
  }
}

//Function for light rotation right
void lightRotateRight() {

  switchState = digitalRead(7);

  lightChange(1, switchState);
  lightChange(0, switchState);
  lightChange(9, switchState);
  lightChange(8, switchState);
  lightChange(7, switchState);
  lightChange(6, switchState);
  lightChange(5, switchState);
  lightChange(4, switchState);
  lightChange(3, switchState);

}

//Function for light rotation left
void lightRotateLeft() {

  switchState = digitalRead(7);

  lightChange(3, switchState);
  lightChange(4, switchState);
  lightChange(5, switchState);
  lightChange(6, switchState);
  lightChange(7, switchState);
  lightChange(8, switchState);
  lightChange(9, switchState);
  lightChange(0, switchState);
  lightChange(1, switchState);

}
