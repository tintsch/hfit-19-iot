// Minimal working example
#include <MKRWAN.h> // Library
#include "arduino_secrets.h" // Keys des Geräts

LoRaModem modem; // modem Objekt initialisieren

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

void setup() {
  modem.begin(EU868); // Modem starten
  modem.joinOTAA(appEui, appKey);  // Am LoRaWAN-Netzwerk (z.B. TTN) anmelden (join)
  modem.minPollInterval(300); // Nicht häufiger als alle 300s = 5min senden
}

void loop() {

  modem.beginPacket(); // Übertragungspaket eröffnen
  modem.write(77); // 77 ist der payload, hier beliebigen Wert reinschreiben
  modem.endPacket(true); // Mit endPacket wird das Paket geschlossen und abgeschickt

  delay(300*1000);
}
