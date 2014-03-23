#include <OneWire.h>

const int BUS_PIN = 13;

OneWire bus(BUS_PIN);

void bytes2temp(byte data[12]) {
    int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

    LowByte = data[0];
    HighByte = data[1];
    TReading = (HighByte << 8) + LowByte;
    SignBit = TReading & 0x8000;  // test most sig bit
    if (SignBit) // negative
    {
      TReading = (TReading ^ 0xffff) + 1; // 2's comp
    }

    Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

    Whole = Tc_100 / 100;  // separate off the whole and fractional portions
    Fract = Tc_100 % 100;

    if (SignBit) // If its negative
    {
       Serial.print("-");
    }
    Serial.print(Whole);
    Serial.print(".");
    if (Fract < 10)
    {
       Serial.print("0");
    }
    Serial.print(Fract);
}

void setup() {
     pinMode(BUS_PIN, INPUT);
     Serial.begin(9600);
     delay(1000);
}

void loop() {
     byte i, present = 0;
     byte addr[8];
     byte data[12];

     delay(1000);

     if (!bus.search(addr)) {
        Serial.print("No more addresses.\n");
        bus.reset_search();
        return;
     }

     Serial.print("ADDRESS=");
     for (i = 0; i < 8; i++) {
        Serial.print(addr[i], HEX);
     }
     Serial.print(" ");


     Serial.print("CRC=");
     if (OneWire::crc8(addr, 7) == addr[7]) {
        Serial.print("GOOD");
     } else {
        Serial.print("BAD");
     }
     Serial.print(" ");

     Serial.print("TYPE=");
     if (addr[0] == 0x10) {
        Serial.print("DS18S20");
     } else if ( addr[0] == 0x28) {
        Serial.print("DS18B20");
     } else {
        Serial.print("UNKNOWN(");
        Serial.print(addr[0], HEX);
        Serial.println(")");
        return;
     }
     Serial.print(" ");

     bus.reset();
     bus.select(addr);
     bus.write(0x44, 1);         // start conversion, with parasite power on at the end

     delay(1000);     // maybe 750ms is enough, maybe not
     // we might do a ds.depower() here, but the reset will take care of it.

     present = bus.reset();
     bus.select(addr);
     bus.write(0xBE);         // Read Scratchpad

     Serial.print("PRESENT=");
     Serial.print(present, HEX);
     Serial.print(" ");

     for (i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = bus.read();
     }
     Serial.print("TEMP=");
     bytes2temp(data);
     Serial.println();
}
