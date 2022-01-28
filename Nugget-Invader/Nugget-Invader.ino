#define up D6 // left button
#define dn D3 // right button
#define lt D7 // left button
#define rt D5 // right button

#include "SH1106Wire.h"
#include "Buttons.h"
#include "MenuInterface.h"
#include "Graphics.h"
#include "WiFiScanner.h"

#include "Attacks.h"
#include "Monitor.h"

WiFiScanner wifiScanner; // create wifiScanner object
SH1106Wire display(0x3C, SDA, SCL); // use builtin i2C
Buttons nuggButtons(up,dn,lt,rt);

MenuInterface invaderMenu; // blank menu canvas
MenuInterface invaderAboutMenu;

MenuInterface attacksSelectAP;
MenuInterface attacksSelectClients;
MenuInterface attacksDeauthStatus;

Attacks attackTool;
Monitor monitorTool;

bool rescan;
bool rescanClients;
uint8_t scrollIndex;

// Nugget Invader tool options
String invaderMenuText[] = {"Attack","Monitor","About"};
String invaderMenuDesc[] {
  "Run WiFi Attacks",
  "Monitor Attacks",
  "Nugget Invader"
};

void invaderAttacks () {Attacks::init();}
void invaderMonitor () {monitorTool.init();}
void invaderAbout() {
  invaderAboutMenu.addFooter("About");
  invaderAboutMenu.addNav(invaderToolMenu);

  // re implement as text method
  display.drawString(0,0,"Nugget Invader v1.0");
  display.drawString(0,10,"by Alex Lynd");
  display.drawString(0,30,"wifinugget.com/");
  display.drawString(0,40,"invader");

  display.display();

  invaderAboutMenu.updateDisplay(false); // override clear option
}

// function array
void (*invaderTools[])(void) = {
  invaderAttacks,
  invaderMonitor,
  invaderAbout,
};

void setup() {
  Serial.begin(115200); delay(300);
  Serial.println("\nStarting Nugget Invader!");
  Serial.println("--------------------------");

  // add to menu interface init
  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(DejaVu_Sans_Mono_10);

  
  // startup tool select menu

  // add header, dynamic scroller position update to scale with screen 
  // add loader menu
  invaderToolMenu();
}

void invaderToolMenu() {
  rescan = true;
  rescanClients = true;
  Serial.println("# entered invader tool menu");
  invaderMenu.addScroller(invaderMenuText, invaderTools, 3);
  invaderMenu.addFooter(invaderMenuDesc);
  invaderMenu.updateDisplay();
}

void loop() {
  return;
}
