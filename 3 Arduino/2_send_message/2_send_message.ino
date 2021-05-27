/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>

#include "arduino_secrets.h"

LoRaModem modem;

// Please enter your sensitive data in the Secret tab (or arduino_secrets.h)

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
  // Now the magic begins ;-)
  // Let's connect via LoRaWAN to the next gateway
  int connected = modem.joinOTAA(appEui, appKey);
  if (connected) {
    Serial.println("Yay! Connected! Helloooo big IoT-world!");
  } else {
    Serial.println("Could not connect; are you indoor? Move near a window and retry");
    while (1) {}
  }
  // Set poll interval to 300 secs.
  modem.minPollInterval(300);
  // NOTE: independently by this setting the modem will
  // not allow to send more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void loop() {
  byte msg = 77;
  Serial.print("Sending: ");
  Serial.print(msg);
  Serial.print(" - converted to HEX: ");
  Serial.print(msg, HEX);
  Serial.print(" ");

  Serial.println();
  int err;
  modem.beginPacket();
  modem.write(msg);
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  delay(300*1000);

}
