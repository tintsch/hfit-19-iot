/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>

// Das machen wir später ;-)
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
  // OTAA = Over The Air Activation
  // Wir möchten uns jetzt mit dem Netzwerk verbinden:
  int connected = modem.joinOTAA(appEui, appKey);
  if (connected) {
    Serial.println("Yay! Connected! Helloooo big IoT-world!");
  } else {
    Serial.println("Could not connect; are you indoor? Move near a window and retry");
    while (1) {}
  }
  // Set poll interval to 300 secs.
  modem.minPollInterval(300);
}

void loop() {

  // was bedeutet '77'?
  // Aufgabe: Wie kann eine von Euch definierte Zahl übertragen werden?
  // - int
  // - float
  // Wie kann diese Zahl als Byte geschrieben werden?
  //
  // Bsp: Temperatur von 23.33 °C (float)
  // Bsp: CO2: 666 ppm (int)
  // ...
  // Tip: Dokumentation lesen: Byte

  // int (0..255) (2^8) => 1 byte
  // int (0 .. 65'536) (2^16) => 2 bytes
  // byte msg = 77;

  // Beispiele für inputs:
  // Datentyp: word = 2 bytes
  int humidity = 45; // Ganzzahl positiv
  int temperature = -12; // Ganzzahl negativ
  word msg = 666; // Ganzzahl > 255 mit zwei Bytes


    // Hier kommt unser Code hin

  
  
  Serial.print("Sending: ");
  Serial.print(msg);
  Serial.print(" - converted to HEX: ");
  Serial.print(msg, HEX);
  Serial.print(" ");

  Serial.println();
  int err;
  // Datenpaket / Payload beginnen
  modem.beginPacket();
  // Payload schreiben (Nutzdaten)
  byte msg1 = 77;
  modem.write(msg1);
  byte msg2 = 255;
  modem.write(msg2);
  
  // Payload beenden
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  // 300 * 1000ms
  delay(300*1000);

}
