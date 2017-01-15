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


#include "BmsDevice.h"

const double BmsDevice::BETA_THERMISTOR = 3435.0;
const double BmsDevice::RB_THERMISTOR = 1800.0;
const double BmsDevice::RT_THERMISTOR = 1500.0;
const double BmsDevice::R0_THERMISTOR = 10000.0;

void BmsDevice::BmsDevice(byte
device_address) :
device_address(device_address) {}

void byte
*
BmsDevice::readRegister(byte
regAddress,
byte length
) const {
if (

RaceUpUtils::isArduinoUnoBoard()

) {
SPI.
setDataMode(SPI_MODE1);
byte logicalAddress = deviceAddress << 1;  // Shift the device bit and clear bit 0
logicalAddress &= 0b11111110;

byte receivedData[20];  // Create buffer for receivedData and clear it
memset(receivedData,
0, sizeof(receivedData));

digitalWrite(SLAVE_SELECT_PIN, LOW);  // take the SS pin low to select the chip:
delayMicroseconds(5);

SPI.
transfer(logicalAddress);  // Send and receive SPI
SPI.
transfer(regAddress);
SPI.
transfer(length);
delayMicroseconds(5);

for (
int i = 0;
i <=
length;
i++) {
receivedData[i] = SPI.transfer(0x00);
}
delayMicroseconds(5);
digitalWrite(SLAVE_SELECT_PIN, HIGH);

SPI.
setDataMode(SPI_MODE0);
return
receivedData;
} else if (

RaceUpUtils::isArduinoDueBoard()

) {
// Take the SS pin low to select the chip
digitalWrite(SLAVE_SELECT_PIN, LOW);

delayMicroseconds(5);

SPI.
beginTransaction(SPISettings(50000, MSBFIRST, SPI_MODE1));

byte logicalAddress = deviceAddress << 1;  // Shift the device bit and clear bit 0
logicalAddress &= 0b11111110;  // logicalAddress &= ~(1 << 0);  // Clear bit 0, test bitClear(x,n)

// Create buffer for receivedData and clear it
byte receivedData[20];
memset(receivedData,
0, sizeof(receivedData));

//  Send and receive SPI
SPI.
transfer(logicalAddress);
SPI.
transfer(regAddress);
SPI.
transfer(length);
delayMicroseconds(1);

for (
int i = 0;
i<length + 1; i++) {
receivedData[i] = SPI.transfer(0x00);
}

delayMicroseconds(5);
digitalWrite(SLAVE_SELECT_PIN, HIGH);  // Take the SS pin high to de-select the chip
SPI.

endTransaction();

return
receivedData;
}

return 0;
}

int BmsDevice::getCellVoltage(byte
cellNumber) const {
byte *cellRaw = readRegister(cellNumber, 0x02);
delay(ONE_CENTSECOND);

double parsed = RaceUpUtils::convertCellVoltage((cellRaw[0] * 256) + cellRaw[1]);
return (int)
parsed;
}

double BmsDevice::getGpaiVbatt(bool dev) const {
    byte * gpaiRaw = readRegister(device_address, GPAI, 0x02);

    if (dev) {
        return ((gpaiRaw[0] * 256) + gpaiRaw[1]) * (100.0 / 3.0) / 16383; // [V]
    } else {
        return ((gpaiRaw[0] * 256) + gpaiRaw[1]) * 2500.0 / 16383; // [mV]
    }
}

double BmsDevice::getTemperature(byte
temperatureToRead) const {
byte *value_read = readRegister(device_address, temperatureToRead, 2);  // read only first 2 bytes
byte tempRaw = (value_read[0] * 0x100) + value_read[1];  // multiply by 256 and add second byte
double value = (tempRaw + 2) / 33046.0;

value = ((1 / value) - 1) * RB_THERMISTOR - RT_THERMISTOR;
value = BETA_THERMISTOR / (log(value / (R0_THERMISTOR * exp(-BETA_THERMISTOR / 298.15))));
return
RaceUpUtils::fromKelvinToCelsius(value);
}

byte *BmsDevice::getStatus() const {
    return readRegister(device_address, DEVICE_STATUS, 1);  // read only 1 bit
}

void BmsDevice::clearAlerts() const {
    byte * value = getStatus();  // clear alert bit in device status register
    value[0] |= 0b00100000;

    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // set alert bit as 1
    value[0] &= 0b11011111;
    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // clear alert bit

    BmsDeviceWriter::bmsDeviceWrite(device_address, ALERT_STATUS, 0xFF);  // write 1's to ALERT_STATUS_REG register
    BmsDeviceWriter::bmsDeviceWrite(device_address, ALERT_STATUS, 0x00);  // Write 0's ALERT_STATUS_REG register
}

void BmsDevice::clearFaults() const {
    byte * value = getStatus();  // clear alert bit in device status register
    value[0] |= 0b01000000;

    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // set alert bit as 1
    value[0] &= 0b10111111;
    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // clear alert bit

    BmsDeviceWriter::bmsDeviceWrite(device_address, FAULT_STATUS, 0xFF);  // write 1's to ALERT_STATUS_REG register
    BmsDeviceWriter::bmsDeviceWrite(device_address, FAULT_STATUS, 0x00);  // write 0's ALERT_STATUS_REG register
}

void BmsDevice::writeRegister(byte
regAddress,
byte regData
) const {
if (

RaceUpUtils::isArduinoUnoBoard()

) {
SPI.
setDataMode(SPI_MODE1);
byte logicalAddress = (deviceAddress << 1) | 0x01;  // Shift the device bit and set bit 0

byte crcInput[3] = {logicalAddress, regAddress, regData};
digitalWrite(SLAVE_SELECT_PIN, LOW);  // Take the SS pin low to select the chip
delayMicroseconds(1);

SPI.
transfer(logicalAddress);  // Send and receive SPI
SPI.
transfer(regAddress);
SPI.
transfer(regData);
SPI.
transfer(pec(crcInput));
delayMicroseconds(1);

digitalWrite(SLAVE_SELECT_PIN, HIGH);  // Take the SS pin high to de-select the chip
SPI.
setDataMode(SPI_MODE0);
} else if (

RaceUpUtils::isArduinoDueBoard()

) {
delayMicroseconds(5);
// Take the SS pin low to select the chip
digitalWrite(SLAVE_SELECT_PIN,LOW);

delayMicroseconds(5);

SPI.
setDataMode(SPI_MODE1);
SPI.
beginTransaction(SPISettings(50000, MSBFIRST, SPI_MODE1));

// Shift the device bit and set bit 0
byte logicalAddress = (deviceAddress << 1) | 0x01;
//logicalAddress |= 1 << 0;  // Set bit 0, test bitSet(x,n)

byte crcInput[3] = {logicalAddress, regAddress, regData};

// Send and receive SPI
SPI.
transfer(logicalAddress);
SPI.
transfer(regAddress);
SPI.
transfer(regData);
SPI.
transfer(pec(crcInput));

delayMicroseconds(5);

// Take the SS pin high to de-select the chip
digitalWrite(SLAVE_SELECT_PIN,HIGH);
}
}

void BmsDevice::setStatus(byte
value) const {
writeRegister(DEVICE_STATUS, value
);
}

byte BmsDevice::pec(byte
crcBuffer[]) {
byte crc = 0;
int temp = 0;
for (
int i = 0;
i < 3; i++) {
temp = crc ^crcBuffer[i];
crc = pgm_read_word_near(crcTable + temp);  // fetch data from flash, load in SRAM
}
return
crc;
}
