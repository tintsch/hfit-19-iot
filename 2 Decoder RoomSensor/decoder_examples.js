/*
    Example payloads:
    Payload: 04011809400302ea01050302be0000
    Output:
    {
    "temperature": 23.28,
    "co2": 490,
    "humidity": 32
    }
*/

// Decoder function for The Things Network:
function Decoder(bytes, port) {
  // bytes: Array
  // port: LoRaWAN-Port
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var co2 = (bytes[8] << 8) + bytes[7];
  if (co2 == 0) {
    decoded.error = 1;
    decoded.co2 = 0;
  } else {
    decoded.co2 = co2;
  }

  var decoded = {
    humidity: bytes[4] * 0.5,
    // temperature: (bytes[3] * 256 + bytes[2]) * 0.01    // Höherwertiges Byte multiplizieren mit 2 Stellen (16*16)
    temperature: ((bytes[3] << 8) + bytes[2]) * 0.01,     // <<: shift left und zusammenzählen
    // temperature: (bytes[3] << 8 | bytes[2]) * 0.01     // shift left und ODER Verknüpfung
    co2: (bytes[8] << 8) + bytes[7]
  };
  return decoded;
}

// ODER: 1 oder 0 = 1
// falsch oder falsch = falsch
// bytes[3] << 8: xxxx'xxxx'0000'0000
// bytes[2]     :           yyyy'yyyy 

// JSON: Objekt
// Besteht aus:
// - key (temp, co2, humidity)
// - value (Wert)
// Jedes Element kann direkt abgerufen werden
var data =  {
    "temperature": 23.28,
    "co2": 490,
    "humidity": 32,
    "meta": {
            "owner": "Valentin",
            "position": "Winterthur"
        }
    };

// Bsp:
// Temperatur:
data.temperature
// Feuchtigkeit
data.humidity
// CO2
data.co2
// owner
data.meta.owner
// metadaten
data.meta => {
    "owner": "Valentin",
    "position": "Winterthur"
}