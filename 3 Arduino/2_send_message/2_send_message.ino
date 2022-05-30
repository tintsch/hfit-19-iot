/* LoRaWAN Send And Receive */

#include <MKRWAN.h>

// LoRaWAN-Keys in diese Datei eintragen:
#include "arduino_secrets.h"
#define LORA_DEBUG     Serial
LoRaModem modem;

// device keys
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

void setup() {
  // Setup wird einmal ausgeführt
  Serial.begin(115200);
  while (!Serial);
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Device EUI is: ");
  Serial.println(modem.deviceEUI());
  Serial.print("FW version: ");
  Serial.println(modem.version());
  // Jetzt gehts los!
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

  // Aufgabe: Wie kann eine von Euch definierte Zahl übertragen werden?
  // - int
  // - float
  // Wie kann diese Zahl als Byte oder Bytearray geschrieben werden?
  //
  // Bsp: Temperatur von 23.33 °C (float)
  // Bsp: CO2: 666 ppm (int)
  // Bsp: Luftfeuchtigkeit: 56%
  // Tip: Arduino Dokumentation lesen: 'Byte'

  // int (0..255) (2^8) => 1 byte
  // int (0 .. 65'536) (2^16) => 2 bytes
  // byte msg = 77;

  // Beispiele für inputs:
  // Datentyp: word = 2 bytes
  // int humidity = 45; // Ganzzahl positiv
  // int temperature = -12; // Ganzzahl negativ
  word msg = 666; // Bsp: Ganzzahl > 255 mit zwei Bytes


  // Hier die Sensoren auslesen
  // 

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
  
  // Payload beenden und absenden mit endPacket(true)
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
  // Warten: 300 * 1000ms
  delay(300*1000);

}
