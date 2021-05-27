
/*
  STFW IoT
  This sketch demonstrates the usage of MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
  Adapted example code for IoT teaching.
*/

#include <MKRWAN.h>

LoRaModem modem;

/*
 * To connect to a LoRaWAN-Gateway some keys for authentication/encryption/transport are needed:
 */
String appEui;
String appKey;
String devAddr;
String nwkSKey;
String appSKey;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Welcome to MKRWAN1310 first configuration sketch");
  Serial.println("Register to your favourite LoRa network and we are ready to go!");
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
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
