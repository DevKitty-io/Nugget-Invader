#pragma once

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "SH1106Wire.h"
#include <Adafruit_NeoPixel.h>

// #include "Graphics.h"
// #include "ESPPL.h"

extern Adafruit_NeoPixel pixels;
extern uint8_t scrollIndex;
extern SH1106Wire display;

// extern MenuInterface monitorPackets;
// extern uint8_t* attack_bits;

// extern uint8_t numScrollerValues;
// extern String* scrollerTextValues;

extern String clients[50];
extern uint8_t numClients;

class WiFiScanner {
  public:
    WiFiScanner();
    
    void init();
    void scanAPs();
    void scanClients(unsigned long scanTime);
    void deauthClients(); //

    String getNetworks();
    void getAPs(); // return list of just APs

    void setDeauthList();
    void monMode();
    
  private:

    uint8_t deauthList[50][6];

    String ssid;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t* BSSID;
    int32_t channel;
    bool isHidden;

    uint16_t packetSize =0;
    uint8_t deauthPacket[26] = {
            /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
            /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
            /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // reciever (target)
            /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source (ap)
            /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // BSSID (ap)
            /* 22 - 23 */ 0x00, 0x00,                         // fragment & squence number
            /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
        };
    // bool clientNotLogged(String clientToLog);
  
};
