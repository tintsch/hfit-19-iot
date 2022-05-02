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
// TODO Fehlercode vom CO2-Sensor abfangen => Fehlercode erzeugen
// TODO Fehlercode vom Temperatursensor abfangen
// TODO Fehlercode vom Feuchtigkeitssensor abfangen
// TODO Stromverbrauch fertig decodieren und kommentieren
// TODO Port überprüfen (Uplink-Port aus der Doku nehmen), ob es ein Uplink mit Daten ist
// TODO function bytes2signedInt für Bytearrays mit Länge 1 und 2 ergänzen

function bytes2signedInt(byte) {
    // ist das Bit ganz links 1?
    // Weshalb? Weil das das Vorzeichen vorgibt.
    // dazu vergleichen wir das Byte mit der Bitfolge 1000'0000
    // 1 << 7 bedeutet: 0000'0001 um 7 Stellen nach links schieben => 1000'0000
    var sign = byte[0] & (1 << 7);
    // Vorzeichen entfernen (wir rechnen es anschliessend wieder ein)
    // Dazu wird das Vorzeichen-Bit auf Null gesetzt
    // Byte & 0111'1111 (logisch UND)
    // Sobald ein Byte einer JS-Variable zugeordnet wird, wird sie in einen 32bit int umgewandelt
    var unsignedInt = (((byte[0] & 0x7F) << 8) | (byte[1] & 0xFF));
    // Der vorzeichenlose int noch mit dem Vorzeichen ergänzen
    var result = unsignedInt;
    if (sign) {
      result = 0xffff0000 | unsignedInt;
    }
    return result;
  }
  
  function Decoder(bytes, port) {
    // bytes: Array
    // port: LoRaWAN-Port
    // Decode an uplink message from a buffer
    // (array) of bytes to an object of fields.
  
    // Teil Batterie (Alice)
    var capacity = 2.6*(10*10*10*10*10*10); // Kapazität in mAh? (= milli Ampere Stunden, steht auf der Batterie)
    // Idee: Den Verbrauch (consumption) übermitteln und mal in Ubidots aufsummieren über die Zeit
    var consumption = bytes[14]*(16*16*16*16) + bytes[13]*(16*16*16) + bytes[12]*(16*16) + bytes[11];
    var battery = 100 / capacity * (capacity - consumption);
  
    var decoded = {
      humidity: bytes[4] * 0.5,
      // temperature: (bytes[3] * 256 + bytes[2]) * 0.01    // Höherwertiges Byte multiplizieren mit 2 Stellen (16*16)
      // temperature: ((bytes[3] << 8) + bytes[2]) * 0.01,     // <<: shift left und zusammenzählen
      // temperature: (bytes[3] << 8 | bytes[2]) * 0.01     // shift left und ODER Verknüpfung
      // Wert mit Vorzeichen korrekt umrechnen:
      temperature: bytes2signedInt([bytes[3], bytes[2]]) * 0.01,
      co2: (bytes[8] << 8) + bytes[7],
      consumption: (bytes[14] << 24) + (bytes[13] << 16) + (bytes[12] << 8) + bytes[11]
    };
    return decoded;
  }

  function Decoder(request) {
    var body = JSON.parse(request.body);
    console.log(body.data.payload_hex);
    var payload = body.data.payload_hex;
    console.log("payload_hex: " + payload);
    
    var decoded = [];
    decoded.push({
        "device": "39703908-0c39-4d95-bc29-a8fe426315b5",
        "field": "TEMPERATURE",
        "value": bytes2signedInt([payload[3], payload[2]]) * 0.01
    });

    
    return decoded;
}  