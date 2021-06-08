#include <MKRWAN.h>

// Variablen um die eingelesenen Sensorwerte zu speichern
int digitalData;
int analogData;

void setup() {
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
  delay(200);
}
