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


#include "BmsDeviceWriter.h"

byte BmsDeviceWriter::pec(byte * crcBuffer) {
    byte crc = 0;
    int temp = 0;
    for (int i = 0; i < 3; i++) {
        temp = crc ^ crcBuffer[i];
        crc = pgm_read_word_near(crcTable + temp);  // fetch data from flash, load in SRAM
    }
    return crc;
}

void BmsDeviceWriter::bmsDeviceWrite(byte
deviceAddress,
byte regAddress, byte
regData) {
#ifdef ARDUINO_UNO
    SPI.setDataMode(SPI_MODE1);
    byte logicalAddress = (deviceAddress << 1) | 0x01;  // Shift the device bit and set bit 0

    byte crcInput[3] = {logicalAddress, regAddress, regData};
    digitalWrite(SLAVE_SELECT_PIN, LOW);  // Take the SS pin low to select the chip
    delayMicroseconds(1);

    SPI.transfer(logicalAddress);  // Send and receive SPI
    SPI.transfer(regAddress);
    SPI.transfer(regData);
    SPI.transfer(pec(crcInput));
    delayMicroseconds(1);

    digitalWrite(SLAVE_SELECT_PIN, HIGH);  // Take the SS pin high to de-select the chip
    SPI.setDataMode(SPI_MODE0);
#endif

#ifdef ARDUINO_DUE
    delayMicroseconds(5);
    // Take the SS pin low to select the chip
    digitalWrite(SLAVE_SELECT_PIN,LOW);

    delayMicroseconds(5);

    SPI.setDataMode(SPI_MODE1);
    SPI.beginTransaction(SPISettings(50000, MSBFIRST, SPI_MODE1));

    // Shift the device bit and set bit 0
    byte logicalAddress = (deviceAddress << 1) | 0x01;
    //logicalAddress |= 1 << 0;  // Set bit 0, test bitSet(x,n)

    byte crcInput[3] = {logicalAddress, regAddress, regData};

    // Send and receive SPI
    SPI.transfer(logicalAddress);
    SPI.transfer(regAddress);
    SPI.transfer(regData);
    SPI.transfer(pec(crcInput));

    delayMicroseconds(5);

    // Take the SS pin high to de-select the chip
    digitalWrite(SLAVE_SELECT_PIN,HIGH);


    //SPI.setDataMode(SPI_MODE0);
    SPI.endTransaction();
#endif
}

void BmsDeviceWriter::writeStatusOfBmsDevice(byte device_address, byte value) {
    bmsDeviceWrite(device_address, DEVICE_STATUS, value);
}
