#pragma once

#include <Arduino.h>
#include "MenuInterface.h"
#include "WiFiScanner.h"
#include <Adafruit_NeoPixel.h>

// extern 
extern WiFiScanner wifiScanner;
extern String accessPoints[50];
extern uint8_t numAPs;
extern String clients[50];
extern uint8_t numClients;
extern bool rescan;
extern bool rescanClients;

extern uint8_t numToDeauth;

extern Adafruit_NeoPixel pixels;

extern uint8_t scrollIndex;
extern String apList[50][5];

extern void invaderToolMenu();

extern MenuInterface attacksSelectAP;
extern MenuInterface attacksSelectClients;
extern MenuInterface attacksDeauthStatus;



class Attacks {
  public:
    Attacks();

    static void init();

    static void selectAP();
    static void selectClients();
    static void deauthStatus();
    
    
  private:
     
    
    
    
};
