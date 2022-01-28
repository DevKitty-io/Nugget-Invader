// Ricardo Oliveira's ESP Pro Library
// github.com/RicardoOliveira/ESPProLib

#ifndef ESPPL_HEADER
#define ESPPL_HEADER

#include <ESP8266WiFi.h>
#define ESPPL_MAC_LEN 6
#define ESPPL_SSID_LEN 33
#define ESPPL_CHANNEL_MIN 1
#define ESPPL_CHANNEL_MAX 14
#define ESPPL_CHANNEL_DEFAULT 1
#define ESPPL_MANAGEMENT_MAC_HEADER_SIZE 36

/*
 * ESP8266 sniffer structures
 */
struct RxControl {
  signed rssi: 8;
  unsigned rate: 4;
  unsigned is_group: 1;
  unsigned: 1;
  unsigned sig_mode: 2;
  unsigned legacy_length: 12;
  unsigned damatch0: 1;
  unsigned damatch1: 1;
  unsigned bssidmatch0: 1;
  unsigned bssidmatch1: 1;
  unsigned MCS: 7;
  unsigned CWB: 1;
  unsigned HT_length: 16;
  unsigned Smoothing: 1;
  unsigned Not_Sounding: 1;
  unsigned: 1;
  unsigned Aggregation: 1;
  unsigned STBC: 2;
  unsigned FEC_CODING: 1;
  unsigned SGI: 1;
  unsigned rxend_state: 8;
  unsigned ampdu_cnt: 8;
  unsigned channel: 4;
  unsigned: 12;
};

struct LenSeq {
  uint16_t length;
  uint16_t seq;
  uint8_t  address3[6];
};

struct sniffer_buf {
  struct RxControl rx_ctrl;
  uint8_t buf[36];
  uint16_t cnt;
  struct LenSeq lenseq[1];
};

struct sniffer_buf2 {
  struct RxControl rx_ctrl;
  uint8_t buf[112];
  uint16_t cnt;
  uint16_t len;
};

/* 
 * ESPProLib structures 
 */
struct esppl_frame_info {
  uint8_t frametype;
  uint8_t framesubtype;
  uint8_t receiveraddr[ESPPL_MAC_LEN];
  uint8_t destinationaddr[ESPPL_MAC_LEN];
  uint8_t transmitteraddr[ESPPL_MAC_LEN];
  uint8_t sourceaddr[ESPPL_MAC_LEN];
  uint8_t bssid[ESPPL_MAC_LEN];  
  uint8_t ssid[ESPPL_SSID_LEN];
  uint8_t ssid_length;
  unsigned channel;
  signed rssi;
  uint16_t seq_num;
  uint8_t raw[512];
  uint8_t raw_length;
  bool isvalid;
};

typedef void (*ESPPL_CB_T) (esppl_frame_info *frame);

// - DS Field
const uint8_t ESPPL_DS_NO     = 0;
const uint8_t ESPPL_DS_TO     = 1;
const uint8_t ESPPL_DS_FROM   = 2;
const uint8_t ESPPL_DS_TOFROM = 3;

// - Frame types
const uint8_t ESPPL_MANAGEMENT = 0;
const uint8_t ESPPL_CONTROL    = 1;
const uint8_t ESPPL_DATA       = 2;

// - Frame subtypes
const uint8_t ESPPL_MANAGEMENT_ASSOCIATION_REQUEST    = 0;
const uint8_t ESPPL_MANAGEMENT_ASSOCIATION_RESPONSE   = 1;
const uint8_t ESPPL_MANAGEMENT_REASSOCIATION_REQUEST  = 2;
const uint8_t ESPPL_MANAGEMENT_REASSOCIATION_RESPONSE = 3;
const uint8_t ESPPL_MANAGEMENT_PROBE_REQUEST          = 4;
const uint8_t ESPPL_MANAGEMENT_PROBE_RESPONSE         = 5;
const uint8_t ESPPL_MANAGEMENT_TIMMING_ADVERTISEMENT  = 6;
const uint8_t ESPPL_MANAGEMENT_RESERVED1              = 7;
const uint8_t ESPPL_MANAGEMENT_BEACON                 = 8;
const uint8_t ESPPL_MANAGEMENT_ATIM                   = 9;
const uint8_t ESPPL_MANAGEMENT_DISASSOCIATION         = 10;
const uint8_t ESPPL_MANAGEMENT_AUTHENTICATION         = 11;
const uint8_t ESPPL_MANAGEMENT_DEAUTHENTICATION       = 12;
const uint8_t ESPPL_MANAGEMENT_ACTION                 = 13;
const uint8_t ESPPL_MANAGEMENT_ACTION_NO_ACK          = 14;
const uint8_t ESPPL_MANAGEMENT_RESERVED2              = 15;

const uint8_t ESPPL_CONTROL_RESERVED1                 = 0;
const uint8_t ESPPL_CONTROL_RESERVED2                 = 1;
const uint8_t ESPPL_CONTROL_RESERVED3                 = 2;
const uint8_t ESPPL_CONTROL_RESERVED4                 = 3;
const uint8_t ESPPL_CONTROL_RESERVED5                 = 4;
const uint8_t ESPPL_CONTROL_RESERVED6                 = 5;
const uint8_t ESPPL_CONTROL_RESERVED7                 = 6;
const uint8_t ESPPL_CONTROL_CONTROL_WRAPPER           = 7;
const uint8_t ESPPL_CONTROL_BLOCK_ACK_REQUEST         = 8;
const uint8_t ESPPL_CONTROL_BLOCK_ACK                 = 9;
const uint8_t ESPPL_CONTROL_PS_POLL                   = 10;
const uint8_t ESPPL_CONTROL_RTS                       = 11;
const uint8_t ESPPL_CONTROL_CTS                       = 12;
const uint8_t ESPPL_CONTROL_ACK                       = 13;
const uint8_t ESPPL_CONTROL_CF_END                    = 14;
const uint8_t ESPPL_CONTROL_CF_END_CF_ACK             = 15;

const uint8_t ESPPL_DATA_DATA                         = 0;
const uint8_t ESPPL_DATA_DATA_CF_ACK                  = 1;
const uint8_t ESPPL_DATA_DATA_CF_POLL                 = 2;
const uint8_t ESPPL_DATA_DATA_CF_ACK_CF_POLL          = 3;
const uint8_t ESPPL_DATA_NULL                         = 4;
const uint8_t ESPPL_DATA_CF_ACK                       = 5;
const uint8_t ESPPL_DATA_CF_POLL                      = 6;
const uint8_t ESPPL_DATA_CF_ACK_CF_POLL               = 7;
const uint8_t ESPPL_DATA_QOS_DATA                     = 8;
const uint8_t ESPPL_DATA_QOS_DATA_CF_ACK              = 9;
const uint8_t ESPPL_DATA_QOS_DATA_CF_ACK_CF_POLL      = 10;
const uint8_t ESPPL_DATA_QOS_NULL                     = 11;
const uint8_t ESPPL_DATA_RESERVED1                    = 12;
const uint8_t ESPPL_DATA_QOS_CF_POLL                  = 13;
const uint8_t ESPPL_DATA_QOS_CF_ACK_CF_POLL           = 14;



//TODO: Reserved

extern "C" {
  #include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int  wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int  wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}

uint8_t esppl_channel = ESPPL_CHANNEL_DEFAULT;
uint8_t esppl_default_mac[ESPPL_MAC_LEN] = {0x00,0x00,0x00,0x00,0x00,0x00};
ESPPL_CB_T user_cb;
int frame_waitlist = 0;
bool esppl_sniffing_enabled = false;

void esppl_buf_to_info(uint8_t *frame, signed rssi, uint16_t len);

/*
 * Promiscuous RX callback function
 */
void esppl_rx_cb(uint8_t *buf, uint16_t len) {
  if (len == sizeof(struct sniffer_buf2)) {
    struct sniffer_buf2 *sniffer = (struct sniffer_buf2*) buf;
    esppl_buf_to_info(sniffer->buf, sniffer->rx_ctrl.rssi, len);
  } else if (len == sizeof(struct RxControl)) {
    struct RxControl *sniffer = (struct RxControl*) buf;
  } else {
    struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
    esppl_buf_to_info(sniffer->buf, sniffer->rx_ctrl.rssi, len);
  }
}

/* 
 * buf to esppl_frame_info structure converter 
 */
void esppl_buf_to_info(uint8_t *frame, signed rssi, uint16_t len) {
  struct esppl_frame_info info;
  uint8_t dstofrom;
  uint8_t pos;
  uint8_t parsecount;

  if (esppl_sniffing_enabled) {
    frame_waitlist++;
    // - "Resets" some fields
    memcpy(info.receiveraddr, esppl_default_mac, ESPPL_MAC_LEN);
    memcpy(info.destinationaddr, esppl_default_mac, ESPPL_MAC_LEN);
    memcpy(info.transmitteraddr, esppl_default_mac, ESPPL_MAC_LEN);
    memcpy(info.sourceaddr, esppl_default_mac, ESPPL_MAC_LEN);
    memcpy(info.bssid, esppl_default_mac, ESPPL_MAC_LEN);
    info.ssid_length = 0;
    info.isvalid = true;
    info.channel = 0;
    info.seq_num = 0;
    // - Populates the fields
    memcpy(info.raw, frame, len - 1);
    info.raw_length = len;
    
    info.frametype = (frame[0] & B00001100) >> 2;
    info.framesubtype = (frame[0] & B11110000) >> 4;
    info.rssi = rssi;
  
    dstofrom = (frame[1] & 3);
  
    switch (info.frametype) {
      case ESPPL_CONTROL: // - Control Frames
        switch (info.framesubtype) {
          case ESPPL_CONTROL_RTS: // - RTS
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN); //?
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN); //?
            break;
          case ESPPL_CONTROL_CTS: // - CTS
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN); //?
            break;
          case ESPPL_CONTROL_ACK: // - ACK
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN); //?
            break;
          case ESPPL_CONTROL_PS_POLL: // - PS-POLL
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN); //?
            memcpy(info.bssid, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN); //?
            break;
          case ESPPL_CONTROL_CF_END: // - CF-END
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);          
            memcpy(info.bssid, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            break;
          case ESPPL_CONTROL_CF_END_CF_ACK: // - CF-END+CF-ACK
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);          
            memcpy(info.bssid, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            break;
          case ESPPL_CONTROL_BLOCK_ACK_REQUEST: // - BlockAckReq
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            break;
          case ESPPL_CONTROL_BLOCK_ACK: // - BlockAck
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            break;
          case ESPPL_CONTROL_CONTROL_WRAPPER: // - Control Wrapper
            //TODO
            break;
        }
        break;
      case ESPPL_DATA: // - Data Frames
        info.seq_num = frame[23] * 0xFF + (frame[22] & 0xF0);
        switch (dstofrom) { // - ToDS FromDS
          case ESPPL_DS_NO: // - ToDS=0 FromDS=0
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.bssid, frame + 4 + ESPPL_MAC_LEN * 2, ESPPL_MAC_LEN);
            break;
          case ESPPL_DS_TO: // - ToDS=1 FromDS=0
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.bssid, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4 + ESPPL_MAC_LEN * 2, ESPPL_MAC_LEN); //MSDU
            break;
          case ESPPL_DS_FROM: // - ToDS=0 FromDS=1
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.bssid, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN * 2, ESPPL_MAC_LEN);
            break;
          case ESPPL_DS_TOFROM: // - ToDS=1 FromDS=1
            memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
            memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
            memcpy(info.destinationaddr, frame + 4 + ESPPL_MAC_LEN * 2, ESPPL_MAC_LEN);
            memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN * 2 + 2, ESPPL_MAC_LEN);
            break;
        }
        break;
      case ESPPL_MANAGEMENT: // - Management Frames
        switch (info.framesubtype) {
          case ESPPL_MANAGEMENT_PROBE_RESPONSE:
          case ESPPL_MANAGEMENT_BEACON:
            // - Parses management frame body
            info.seq_num = frame[23] * 0xFF + (frame[22] & 0xF0);
            pos = ESPPL_MANAGEMENT_MAC_HEADER_SIZE;
            parsecount = 0;
            while (pos < len && parsecount < 4) {
              switch (frame[pos]) {
                case 0: // - SSID
                  info.ssid_length = frame[pos + 1];
                  if (info.ssid_length > 32 || info.ssid_length < 0) {
                    info.ssid_length = 0;
                  }
                  memcpy(info.ssid, frame + pos + 2, info.ssid_length);
                  break;
                case 3: // - Channel
                  info.channel = (int) frame[pos + 2];
                  break;
                default:
                  break;
              }
              parsecount++; // - Avoid bad parsing or infinite loop
              pos += frame[pos + 1] + 2;
            }
          default:
            break;
        }
        memcpy(info.receiveraddr, frame + 4, ESPPL_MAC_LEN);
        memcpy(info.destinationaddr, frame + 4, ESPPL_MAC_LEN);
        memcpy(info.transmitteraddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
        memcpy(info.sourceaddr, frame + 4 + ESPPL_MAC_LEN, ESPPL_MAC_LEN);
        memcpy(info.bssid, frame + 4 + ESPPL_MAC_LEN * 2, ESPPL_MAC_LEN);
        break;
      default:
        info.isvalid = false; //TODO Proper checksum validation
    }
  
    // - User callback function
    if (info.isvalid) {
      user_cb(&info);
    }
    frame_waitlist--;
  }
}

/* 
 * Change channel 
 */
void esppl_set_channel(int channel) {
  wifi_set_channel(channel);
  esppl_channel = channel;
}

/* 
 * Allows some time to process the frames 
 */
bool esppl_process_frames() {
  delay(10);
  return frame_waitlist != 0;
}

/*
 * Initialization function
 */
void esppl_init(ESPPL_CB_T cb) {
  user_cb = cb;
  frame_waitlist = 0;
  wifi_station_disconnect();
  wifi_set_opmode(STATION_MODE);
  wifi_set_channel(esppl_channel);
  wifi_promiscuous_enable(false);
  wifi_set_promiscuous_rx_cb(esppl_rx_cb);
  wifi_promiscuous_enable(true);
  esppl_sniffing_enabled = false;
}

/*
 * Start sniffing
 */
void esppl_sniffing_start() {
  esppl_sniffing_enabled = true;
}

/*
 * Stop sniffing
 */
void esppl_sniffing_stop() {
  esppl_sniffing_enabled = false;
}

#endif
