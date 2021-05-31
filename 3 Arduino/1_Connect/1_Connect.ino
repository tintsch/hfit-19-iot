
/*
  STFW IoT
  This sketch demonstrates the usage of MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
  Adapted example code for IoT teaching.
*/

#include <MKRWAN.h>

LoRaModem modem;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Arduino MKRWAN 1310: Geräteparameter auslesen");
  if (!modem.begin(EU868)) {
    Serial.println("[Fehler] LoRa-Modem konnte nicht gestartet werden.");
    while (1) {}
  };
  Serial.print("[Info] LoRa-Modem (Modul) Version: ");
  Serial.println(modem.version());
  Serial.print("[Info] Device_EUI: ");
  Serial.println(modem.deviceEUI());

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
 
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

}
