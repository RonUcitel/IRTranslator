#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

#define NO_LED_FEEDBACK_CODE

#define sb_vol_up 0x20, 0x42
#define sb_vol_down 0x20, 0x43
#define sb_mute 0x20, 0x1B

#define tv_Address 0x7
#define tv_vol_up 0x7
#define tv_vol_down 0xB
#define tv_mute 0xF



volatile bool sDataJustReceived = false;
void ReceiveCompleteCallbackHandler();
void SendIR(uint16_t aAddress, uint8_t aCommand);

void setup() {
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  IrReceiver.registerReceiveCompleteCallback(ReceiveCompleteCallbackHandler);

  IrSender.begin();
}

void loop() {
  while (!sDataJustReceived) {
    }
  sDataJustReceived = false;

  if(IrReceiver.decode()) {
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.address == tv_Address) {
        if (IrReceiver.decodedIRData.command == tv_vol_up) {
            SendIR(sb_vol_up);
        } else if (IrReceiver.decodedIRData.command == tv_vol_down) {
            SendIR(sb_vol_down);
        } else if (IrReceiver.decodedIRData.command == tv_mute) {
            SendIR(sb_mute);
        }
    }
  }
}

void ReceiveCompleteCallbackHandler() {
    sDataJustReceived = true;
}

void SendIR(uint16_t aAddress, uint8_t aCommand){
      IrSender.sendNEC(aAddress, aCommand, 0);
 }
