/*
 * Decoder für Arduino MKRWAN 1310
 * => Lesbare Namen für JSON-keys verwenden
 * => Selber entscheiden wie die Information übertragen wird, d.h. auf dem Arduino
 *    definieren was welches Bit/Byte bedeutet und im Decoder genau gleich umsetzen
 *
 * Beispiel für das Katzentörli
*/

function decodeUplink(input) {
  return {
    data: {
      // bytes: input.bytes,
      catDoorOpen: input.bytes[0]
    },
    warnings: [],
    errors: []
  };
}