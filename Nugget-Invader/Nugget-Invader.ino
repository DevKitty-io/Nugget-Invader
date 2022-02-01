#define up D6 // left button
#define dn D3 // right button
#define lt D7 // left button
#define rt D5 // right button

#include "SH1106Wire.h"
#include "Buttons.h"
#include "MenuInterface.h"
#include "Graphics.h"
#include "WiFiScanner.h"
#include <Adafruit_NeoPixel.h>

#include "Attacks.h"
#include "Monitor.h"

Adafruit_NeoPixel pixels {1, D8, NEO_GRB + NEO_KHZ800 }; // initialize 1 NeoPixel on D8

WiFiScanner wifiScanner; // create wifiScanner object
SH1106Wire display(0x3C, SDA, SCL); // use builtin i2C
Buttons nuggButtons(up,dn,lt,rt);

MenuInterface invaderMenu; // blank menu canvas
MenuInterface invaderAboutMenu;

MenuInterface attacksSelectAP;
MenuInterface attacksSelectClients;
MenuInterface attacksDeauthStatus;

MenuInterface monitorPackets;

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

unsigned char* invaderMenuIcons[] = {
  invader_attack_bits,
  invader_monitor_bits,
  invader_about_bits
};

void invaderAttacks () {Attacks::init();}
void invaderMonitor () {monitorTool.main();}
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
  Serial.begin(115200); delay(3000);
  pixels.begin(); pixels.clear(); 
  pixels.setBrightness(100);

  Serial.println("\nNugget Invader v1.0");
  Serial.println("by Alex Lynd");
  Serial.println("--------------------------");

  // add to menu interface init
  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(DejaVu_Sans_Mono_10);

  display.drawXbm(0,0,128,64,invader_bits);
  display.display();
  delay(1500);
  display.clear(); display.display();
  
  // startup tool select menu

  // add header, dynamic scroller position update to scale with screen 
  // add loader menu
  invaderToolMenu();
}

void invaderToolMenu() {
  rescan = true;
  rescanClients = true;
  // Serial.println("# entered invader tool menu");
  invaderMenu.addScroller(invaderMenuText, invaderTools, 3);
  invaderMenu.addFooter(invaderMenuDesc, invaderMenuIcons);
  invaderMenu.updateDisplay();
}

void loop() {
  return;
}
