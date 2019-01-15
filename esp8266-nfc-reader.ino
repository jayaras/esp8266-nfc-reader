#include <Homie.h>

// https://github.com/Seeed-Studio/PN532  
#include <PN532_I2C.h>
#include <PN532.h>

#include <Wire.h>

PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

HomieNode nfcNode("rfid","rfid");

bool has_card = false;
uint8_t last_uid[] = { 0, 0, 0, 0, 0, 0, 0 };
char uidstring[15];


void loopHandler() {

  uint8_t retval;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  retval = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (retval) {
    has_card = true;

    if (memcmp(last_uid, uid, 7)) {
      memcpy(last_uid, uid, 7);

      switch (uidLength) {
        case 4:
          sprintf(uidstring, "%02x%02x%02x%02x\0", uid[0], uid[1], uid[2], uid[3]);
          break;
        case 7:
          sprintf(uidstring, "%02x%02x%02x%02x%02x%02x%02x\0", uid[0], uid[1], uid[2], uid[3], uid[4], uid[5], uid[6]);
          break;

      }

      Homie.getLogger() << "Card Found With UID: " << uidstring << endl;
      
      nfcNode.setProperty("uid").setRetained(false).send(uidstring);
      nfcNode.setProperty("present").setRetained(false).send("true");
    }


  } else {
    if (has_card) {
      // card went away.
      uint8_t blank_uid[] = { 0, 0, 0, 0, 0, 0, 0 };

      Homie.getLogger() << "Card Moved Away: " << uidstring << endl;

      nfcNode.setProperty("uid").setRetained(false).send("");
      nfcNode.setProperty("present").setRetained(false).send("false");
      nfcNode.setProperty("previous_uid").setRetained(false).send(uidstring);

      memcpy(last_uid, blank_uid, 7);

      has_card = false;


    }

  }

}


void cardReaderSetup() {
  Wire.setClockStretchLimit(2000);
  Wire.begin(12, 14);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
    // I should try resetting the board here.. and then re-init'ing.
  }

  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  nfc.setPassiveActivationRetries(1);
  nfc.SAMConfig();
}


void setup() {
  Homie_setFirmware("nfc-reader", "1.2.0");

  Homie.setSetupFunction(cardReaderSetup);
  Homie.setLoopFunction(loopHandler);

  nfcNode.advertise("uid");
  nfcNode.advertise("present");
  nfcNode.advertise("previous_uid");

  Homie.setup();
}

void loop() {
  Homie.loop();

}
