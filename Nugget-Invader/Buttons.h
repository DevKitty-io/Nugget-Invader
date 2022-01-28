#pragma once

#include "Arduino.h"

 class Buttons {
  
  public:
    Buttons(int8_t upBtnPin, int8_t dnBtnPin, int8_t ltBtnPin, int8_t rtBtnPin);
    void init();
    int8_t getPress();
    int8_t pressStatus;
    
    bool upPressed();
    bool dnPressed();
    bool ltPressed();
    bool rtPressed();
    
  private:
    int8_t upBtnPin;
    int8_t dnBtnPin;
    int8_t ltBtnPin;
    int8_t rtBtnPin;
 };
