#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

class Deauth {
  public:
    Deauth();
    void sendDeauth();
  
  private:
    uint16_t packetSize = 0;
    
    uint8_t deauthPacket[26] = {
      0xC0, 0x00,                         // type / subtype
      0x00, 0x00,                         // duration 
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // receiver address
      0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source address
      0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // AP BSSID 
      0x00, 0x00,                         // fragment / sequence number
      0x01, 0x00                          // reason code
    };
    
};
