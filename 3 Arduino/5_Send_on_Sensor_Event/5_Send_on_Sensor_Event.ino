/* 
 *  Sensor auslesen
 *  Resultat des Sensors an das TTN senden
 *  wenn ein Sensorereignis ausgelöst wird:
 *  - Kippen, Nähe, Bewegung, Schallpegel, Temperaturschwellwert, ...
 */
#include <MKRWAN.h>

// Die Geräte-Keys werden separat gespeichert:
#include "arduino_secrets.h"
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

// LoRaWAN Modem Instanz erstellen
LoRaModem modem;

// Variablen um die eingelesenen Sensorwerte zu speichern
int digitalData;
int analogData;
int err;

void setup() {
  // LoRaWAN Modem initialisieren
  // EU868 ist die Sendefrequenz in Europa
  if (!modem.begin(EU868)) {
    Serial.println("[LoRaWAN-Modem] konnte nicht gestartet werden");
    while (1) {} // hier Programm blockieren
  } else {
    Serial.println("[LoRaWAN-Modem] gestartet");  
  };
  // Device EUI ausgeben
  Serial.print("[LoRaWAN-Modem] Device-EUI: ");
  Serial.println(modem.deviceEUI());
  // Now the magic begins ;-)
  // Arduino MKRWAN1310 mit TTN verbinden
  // OTAA = Over The Air Activation
  int connected = modem.joinOTAA(appEui, appKey);
  if (connected) {
    Serial.println("[LoRaWAN-Modem] Juhuu, mit TTN verbunden. Hallo grosse IoT-Welt!");
  } else {
    Serial.println("[LoRaWAN-Modem] Verbindung mit TTN nicht möglich, schlechter Empfang?");
    while (1) {}
  }
  // Höchstens alle 300s die Verbindung checken
  modem.minPollInterval(300);
  
  // D0, digital pin 0 als Input definieren
  pinMode(0, INPUT);
  // A0, analog pin 0 als Input definieren
  pinMode(A0, INPUT);
  // Serielle Verbindung öffnen um auf der Console
  // Debug-Nachrichten auszugeben
  Serial.begin(115200);
  while (!Serial);
  // Starten mit Info auf Console
  Serial.println("Sensortest:");
}

// Alles in dieser Funktion wird immer wieder ausgeführt...
void loop() {
  // Digitaleingang einlesen
  // Resultat (digitalData) ist HIGH (3.3V) oder LOW (0V)
  digitalData = digitalRead(0);
  Serial.println(digitalData);
  // Resultat (analogData) ist zwischen 0..1023
  // Der Analogeingang hat eine Auflösung von 10bits
  // 0 entspricht 0V, 1023 entspricht 3.3V
  analogData = analogRead(A0);
  Serial.println(analogData);
  // Verzögerung in Millisekunden bis die Funktion loop() erneut aufgerufen wird.
  // Beispiel: Senden wenn Digitaleingang HIGH ist
  if (digitalData == HIGH) {
    // Datenpaket / Payload beginnen
    modem.beginPacket();
    // Payload schreiben (Nutzdaten)
    byte msg = 1; // 1 = HIGH
    modem.write(msg); // Dieser Befehl kann für jedes Byte wiederholt werden
    // Payload abschliessen und versenden
    err = modem.endPacket(true);
    if (err > 0) {
      Serial.println("[LoRaWAN-Modem] Payload versendet.");
      } else {
        Serial.println("[LoRaWAN-Modem] Error beim Versenden des Payloads.");
        Serial.println("[LoRaWAN-Modem] Evtl. ein paar Minuten warten, evtl. maximale Anzahl Nachrichten erreicht.");
      }
    } // end if 'senden'
  
  delay(200);
}
