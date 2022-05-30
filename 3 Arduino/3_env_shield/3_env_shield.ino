#include <Arduino_MKRENV.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!ENV.begin()) {
    Serial.println("MKR ENV Shield konnte nicht initialisiert werden");
    while (1); // unendlich lange warten...
  }
}

void loop() {
  float temperature = ENV.readTemperature();
  float humidity    = ENV.readHumidity();
  float pressure    = ENV.readPressure();
  float illuminance = ENV.readIlluminance();

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure    = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lx");

  delay(5000);
}
