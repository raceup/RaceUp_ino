/**
 * Copyright 2016 - 2017 RaceUp Team Unipd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "BmsDeviceReader.h"
#include "../Utils.h"

#include "../data.h"

const double BmsDeviceReader::BETA_THERMISTOR = 3435.0;
const double BmsDeviceReader::RB_THERMISTOR = 1800.0;
const double BmsDeviceReader::RT_THERMISTOR = 1500.0;
const double BmsDeviceReader::R0_THERMISTOR = 10000.0;

byte *BmsDeviceReader::bmsDeviceRead(byte
deviceAddress,
byte regAddress, byte
length) {
#ifdef ARDUINO_UNO
SPI.setDataMode(SPI_MODE1);
byte logicalAddress = deviceAddress << 1;  // Shift the device bit and clear bit 0
logicalAddress &= 0b11111110;

byte receivedData[20];  // Create buffer for receivedData and clear it
memset(receivedData, 0, sizeof(receivedData));

digitalWrite(SLAVE_SELECT_PIN, LOW);  // take the SS pin low to select the chip:
delayMicroseconds(5);

SPI.transfer(logicalAddress);  // Send and receive SPI
SPI.transfer(regAddress);
SPI.transfer(length);
delayMicroseconds(5);

for (int i = 0; i <= length; i++) {
    receivedData[i] = SPI.transfer(0x00);
}
delayMicroseconds(5);
digitalWrite(SLAVE_SELECT_PIN,HIGH);

SPI.setDataMode(SPI_MODE0);
return receivedData;

#endif

#ifdef ARDUINO_DUE
// Take the SS pin low to select the chip
digitalWrite(SLAVE_SELECT_PIN,LOW);

delayMicroseconds(5);

//SPI.setDataMode(SPI_MODE1);

SPI.beginTransaction(SPISettings(50000, MSBFIRST, SPI_MODE1));

// Shift the device bit and clear bit 0
byte logicalAddress = deviceAddress << 1;
//logicalAddress &= ~(1 << 0);  // Clear bit 0, test bitClear(x,n)
logicalAddress &= 0b11111110;

// Create buffer for receivedData and clear it
byte receivedData[20];
memset(receivedData, 0, sizeof(receivedData));

//  Send and receive SPI
SPI.transfer(logicalAddress);
SPI.transfer(regAddress);
SPI.transfer(length);
delayMicroseconds(1);
for (int i = 0; i < length + 1; i++) {
    receivedData[i] = SPI.transfer(0x00);
}

delayMicroseconds(5);

// Take the SS pin high to de-select the chip
digitalWrite(SLAVE_SELECT_PIN,HIGH);


//SPI.setDataMode(SPI_MODE0);
SPI.endTransaction();

// Return data read from registers
return receivedData;
#endif

return 0;
}

double BmsDeviceReader::getTemperature(byte
device_address,
byte temperature
) {
byte *value_read = bmsDeviceRead(device_address, temperature, 2);  // read only first 2 bytes
byte tempRaw = (value_read[0] * 0x100) + value_read[1];  // multiply by 256 and add second byte
double value = (tempRaw + 2) / 33046.0;
value = ((1 / value) - 1) * BmsDeviceReader::RB_THERMISTOR - BmsDeviceReader::RT_THERMISTOR;
value = BmsDeviceReader::BETA_THERMISTOR /
        (log(value / (BmsDeviceReader::R0_THERMISTOR * exp(-BmsDeviceReader::BETA_THERMISTOR / 298.15))));
return
Utils::fromKelvinToCelsius(value);
}

double BmsDeviceReader::getGpaiVbatt(byte
device_address,
bool dev
) {
byte *gpaiRaw = bmsDeviceRead(device_address, GPAI, 0x02);

if (dev) {
return ((gpaiRaw[0] * 256) + gpaiRaw[1]) * (100.0 / 3.0) / 16383; // [V]
} else {
return ((gpaiRaw[0] * 256) + gpaiRaw[1]) * 2500.0 / 16383; // [mV]
}
}

int BmsDeviceReader::getCellVoltage(byte
deviceAddress,
byte cellNumber
) {
byte *cellRaw = bmsDeviceRead(deviceAddress, cellNumber, 0x02);
delay(ONE_CENTSECOND);

double parsed = Utils::convertCellVoltage((cellRaw[0] * 256) + cellRaw[1]);
return (int)
parsed;
}

byte *BmsDeviceReader::getBmsDeviceStatus(byte
device_address) {
return
bmsDeviceRead(device_address, DEVICE_STATUS,
1);  // read only 1 bit
}
