#pragma once

#include <Arduino.h>
#include "MenuInterface.h"
#include "Graphics.h"

extern MenuInterface monitorPackets;
extern void invaderToolMenu();
// extern uint8_t attack_bits;

class Monitor {
  public:
    Monitor();
    void init();
    void main();

  private:
};
