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

  // Teil Batterie (Alice)
  var capacity = 2.6*(10*10*10*10*10*10);
  var consumption = bytes[14]*(16*16*16*16) + bytes[13]*(16*16*16) + bytes[12]*(16*16) + bytes[11];
  var battery = 100 / capacity * (capacity - consumption);

  var decoded = {
    humidity: bytes[4] * 0.5,
    // temperature: (bytes[3] * 256 + bytes[2]) * 0.01    // Höherwertiges Byte multiplizieren mit 2 Stellen (16*16)
    temperature: ((bytes[3] << 8) + bytes[2]) * 0.01,     // <<: shift left und zusammenzählen
    // temperature: (bytes[3] << 8 | bytes[2]) * 0.01     // shift left und ODER Verknüpfung
    co2: (bytes[8] << 8) + bytes[7],
    battery: battery
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