function Decoder(bytes, port) {
  // bytes: Array
  // port: LoRaWAN-Port
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.

  var decoded = {
    humidity: bytes[4] * 0.5,
    temperature: (bytes[3] * 256 + bytes[2]) * 0.01
    // temperature: (bytes[3] << 8 bytes[2]) * 0.01               // shift left
  };
  

  return decoded;
}