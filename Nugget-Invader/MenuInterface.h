#pragma once

#include "Arduino.h"
#include "SH1106Wire.h"
#include "Buttons.h"
#include "WiFiScanner.h"

extern SH1106Wire display;
extern Buttons nuggButtons;

extern uint8_t scrollIndex;
extern bool rescanClients;
extern WiFiScanner wifiScanner; // this shouldn't be here

class MenuInterface {
  public:
    MenuInterface();
    
    // basic lateral scrolling menu w/ arrows
    MenuInterface(String menuText, int8_t numArrows);
    
    void init();
    void addTitle();
    void addHeader(String headerText, String secondaryText);

    void addLoader(bool ready, uint8_t timeEstimate);
    
    /* Footer */
    void addFooter(String* footerTextValues, unsigned char* scrollIconBits[]);
    void addFooter(String footerText);

    void updateFooterText(String footerText);
    
    
    /* Scroller Menu */
    void addScroller(String* scrollerTextValues, uint8_t numScrollerValues);
    void addScroller(String* scrollerTextValues, void (**scrollermethodList)(), uint8_t numScrollerValues);
    
    void addScrollerSelect(String* scrollerTextValues, uint8_t numScrollerValues);
    uint8_t numScrollerValues;

    /* Dashboard Interface */
    void addDashboard(unsigned char* dbGraphics, String* dbText, uint8_t dbCount);

    void updateDisplay();
    void updateDisplay(bool override);
    void updateDisplayManual();

    void addNav(void (*function1)(), void (*function2)());
    void addNav(void (*function1)());
    
    static void drawLoadingScreen();

    void addSimpleMonitor(uint8_t monitorCount);
    
    
  private:

    unsigned char** scrollerIconBits;

    uint8_t monitorCount;
    bool monitorEn = false;

    uint8_t navCount = 0;
    String menuText;
    String headerText, secondaryText;
    int8_t numArrows;
    
    bool scrollerMenu  = false;
    bool scrollerSelectMenu = false;
    bool headerEnabled = false;

    bool footerEnabled = false;
    bool dynamicFooter = false;

    int8_t  scrollerPos;
    String* scrollerTextValues;
  
    void updateScroller();
    String* footerTextValues;
    String footerText;

    void (*function1)();
    void (*function2)();
    void (**scrollerMethodList)();

    unsigned char* dbGraphics;
    uint8_t dbCount;
    String* dbText;

    // update functions
    void updateFooter();
    void updateHeader();
    
};
