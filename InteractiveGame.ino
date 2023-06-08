//Author: Sinjin Small
//ENGR 103 Final Game
//PROF. Udell

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h> 


int score = 0;
int buttonStatus;
int switchState;

AsyncDelay delay_fastLightCycle;
AsyncDelay delay_slowLightCycle;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  pinMode(5, INPUT_PULLDOWN);
  pinMode(7, INPUT);
  delay_fastLightCycle.start(2700, AsyncDelay::MILLIS);
  delay_slowLightCycle.start(4500, AsyncDelay::MILLIS);
}

void loop() {
  // put your main code here, to run repeatedly:

  CircuitPlayground.setPixelColor(2, 0, 255, 0);
  
  
  int direction;
  direction = score % 2;
  

  if(direction == 0) {
    lightRotateRight();
  }
  else {
    lightRotateLeft();
  }

  switchState = digitalRead(7);


if (switchState) {
  if (delay_slowLightCycle.isExpired()) { 
     buttonStatus = digitalRead(5);
     Serial.println(buttonStatus);
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
      Serial.println(buttonStatus);
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


if(score == 10) {
  CircuitPlayground.clearPixels();

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0);
    CircuitPlayground.playTone(100 * i, 100);
  }
}

}



int lightChange(int lightNum, bool speed) {
  if(speed) {
  CircuitPlayground.setPixelColor(lightNum, 255, 255, 255);
  delay(50);
  CircuitPlayground.setPixelColor(lightNum, 0, 0, 0);
  delay(250);
  }
  else {
  CircuitPlayground.setPixelColor(lightNum, 255, 255, 255);
  delay(250);
  CircuitPlayground.setPixelColor(lightNum, 0, 0, 0);
  delay(250);
  }
}

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
