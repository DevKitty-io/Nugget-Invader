#include "Buttons.h"

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;    // the debounce time; increase if the output flickers

// button states and previous states
int upBtnState = 0;
int dnBtnState = 0; 
int ltBtnState = 0; 
int rtBtnState = 0; 

int prevPress = 0;
int currPress = 0;

Buttons::Buttons(int8_t upBtnPin, int8_t dnBtnPin, int8_t ltBtnPin, int8_t rtBtnPin) {
  this->upBtnPin = upBtnPin;
  this->dnBtnPin = dnBtnPin;
  this->ltBtnPin = ltBtnPin;
  this->rtBtnPin = rtBtnPin;
  
  init();
}

// get pressed buttons with debounce
int8_t Buttons::getPress() {
  upBtnState = digitalRead(upBtnPin);
  dnBtnState = digitalRead(dnBtnPin);
  ltBtnState = digitalRead(ltBtnPin);
  rtBtnState = digitalRead(rtBtnPin);

  if      (upBtnState == 0) { currPress = 1; }
  else if (dnBtnState == 0) { currPress = 2; }
  else if (ltBtnState == 0) { currPress = 3; }
  else if (rtBtnState == 0) { currPress = 4; }
  else currPress = 0;

//  if (currPress!=prevPress) {
//    lastDebounceTime = millis();
//  }
//
//  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currPress!= prevPress and currPress>0) {
      prevPress = currPress;
      pressStatus = currPress;  
    }
    else {
      prevPress = currPress;
      pressStatus = -1;
    }
    
    return pressStatus;
//  }
}

// wrapper functions to check if individual buttons pressed
bool Buttons::upPressed() { return(pressStatus==1); }
bool Buttons::dnPressed() { return(pressStatus==2); }
bool Buttons::ltPressed() { return(pressStatus==3); }
bool Buttons::rtPressed() { return(pressStatus==4); }

void Buttons::init() {
  pinMode(upBtnPin, INPUT_PULLUP);
  pinMode(dnBtnPin, INPUT_PULLUP);
  pinMode(ltBtnPin, INPUT_PULLUP);
  pinMode(rtBtnPin, INPUT_PULLUP);
}
