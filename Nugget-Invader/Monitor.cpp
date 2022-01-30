#include "Monitor.h"
#include "MenuInterface.h"
#include "WiFiScanner.h"

extern WiFiScanner wifiScanner;

Monitor::Monitor() {
  
}

void Monitor::main() {
    // monitorPackets.addFooter("PACKET MONITOR");
    // monitorPackets.addHeader("Network","CH:03");
    // monitorPackets.addNav(invaderToolMenu);
    wifiScanner.monMode();



//     while(true) {
       
//         
//         delay(0);
//     }   

}
