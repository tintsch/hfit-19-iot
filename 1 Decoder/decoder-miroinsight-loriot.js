/**

      In this editor, you can define your custom javascript code to parse the incoming data.	

      The following variables are available:

      	data     : hex string of the data

      	p        : array of bytes represented as string of 2 hex digits 

      	v        : array of bytes represented as integers

      	msg.EUI  : device EUI

      	msg.fcnt : message frame counter

      	msg.port : message port field

      	msg.ts   : message timestamp as number (epoch)

      Last line of your script will be printed to the data payload column.

      **/


/** Helper functions **/

function toHexString(byteArray) {
  var s = '';
  byteArray.forEach(function(byte) {
    s += ('0' + (byte & 0xFF).toString(16)).slice(-2);
  });
  return s;
}

function DecodeTemperature( hexdata ) {
    return ((hexdata[1] * 256) + hexdata[0]) / 100.0;
}

function DecodeHumidity( hexdata ) {
    return hexdata[2] * 0.5;
}

function Decode_Charge( hexdata ) {
    return ((((((hexdata[3] << 8) + hexdata[2]) << 8) + hexdata[1]) << 8) + hexdata[0] );
}

function Decode_CO2( hexdata ) {
    return (hexdata[1] << 8) + hexdata[0];
}

function decodeFromHex(fPort, bytes) {
    // Decode an uplink message from a buffer
    // (array) of bytes to an object of fields.

    var dlen    = 0;
    var dtyp    = 0;
    var dstop   = 0;
    var n       = 0;
    var idx     = 0;
    var ds      = [];
    var ts      = Date.now();
    var steps   = 15*60*1000; // This is just the default, need to be adapted if changed via downlink
    var count   = 0;
    var obj     = {};

    telemetry = [];
    attributes = {};

    if ( fPort == 15 ) {
        n   = bytes.length;
        idx = 0;

        while ( (n - idx) > 2 ) {
            // get DS length and type
            // length is number of bytes without length byte
            // mark first byte after DS as dstop

            dlen  = bytes[idx];
            idx++;
            dtyp  = bytes[idx];
            dstop = idx + dlen;
            idx++;

            switch (dtyp) {
                case 1:
                    // DS = temparature (1 byte) and humidity (2 bytes)
                    count = (dlen-1)/3-1;
                    while ( idx <= (dstop - 3) ) {
                        ds = bytes.slice(idx,idx+3);
                        obj = {
                            'ts': ts - count*steps,
                            'values': {
                                'temperature': DecodeTemperature(ds),
                                'humidity': DecodeHumidity(ds),
                                'sampleNum': count,
                            }
                        };
                        telemetry.push(obj);
                        idx += 3;
                        count--;
                    }
                    break;
                case 2:
                    // DS = CO2 ppM (2 bytes)
                    count = (dlen-1)/2-1;
                    while ( idx <= (dstop - 2) ) {
                         ds = bytes.slice(idx,idx+2);
                         obj = {
                            'ts': ts - count*steps,
                            'values': {
                                'co2': Decode_CO2(ds),
                                'sampleNum': count,
                            }
                         };
                         telemetry.push(obj);
                         idx += 2;
                         count--;
                    }
                    break;
                case 3:
                    // DS = consumed charge [uAh] (4 bytes)
                    count = (dlen-1)/4-1;
                    while ( idx <= (dstop - 4) ) {
                        ds = bytes.slice(idx,idx+4);
                        obj = {
                            'ts': ts - count*steps,
                            'values': {
                                'charge': Decode_Charge(ds),
                            }
                        };
                        telemetry.push(obj);
                        idx += 4;
                        count--;
                    }
                    break;
                case 9:
                    // DS = voltage [V] (2 bytes)
                    ds = bytes.slice(idx,idx+2);
                    telemetry.push({'voltage': ((ds[1] << 8) + ds[0]) / 100.0});
                    idx += 2;
                    break;
                case 5:
                    // DS = interval settings
                    ds = bytes.slice(idx,idx+4);
                    attributes.interval = (ds[1] << 8) + ds[0];
                    attributes.nsamples = ds[2] + 1;
                    attributes.confirmedMessages = Boolean(ds[3] & (1 << 7));
                    attributes.led = Boolean(ds[3] & (1 << 6));
                    attributes.adr = Boolean(ds[3] & (1 << 5));
                    attributes.nbretrans = ds[3] & 0x0f;
                    idx += 4;
                    break;
                case 6:
                    // DS = co2 settings
                    ds = bytes.slice(idx,idx+6);
                    attributes.co2period = (ds[1] << 8) + ds[0];
                    attributes.co2subsamples = (ds[3] << 8) + ds[2];
                    attributes.co2calibperiod = (ds[5] << 8) + ds[4];
                    idx += 6;
                    break;
                case 10:
                    // DS = firmware hash
                    ds = bytes.slice(idx,idx+4);
                    attributes.firmware = toHexString(ds.reverse());
                    idx += 4;
                    break;
                default:
                    // stop if type is unknown
                    idx = dstop;
                    break;
            }
            if ( idx > dstop ) {
                idx = dstop;
            }
        }
    }
    return {'telemetry': telemetry, 'attributes': attributes};
}

var result = decodeFromHex(msg.port, p)
result;
//JSON.stringify(result);