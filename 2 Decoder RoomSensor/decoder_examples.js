// Beispiele für JSON

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