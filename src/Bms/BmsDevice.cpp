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

void BmsDevice::clearAlertsOnBmsDevice(byte
device_address) {
    byte *value = BmsDeviceReader::getBmsDeviceStatus(device_address);  // clear alert bit in device status register
    value[0] |= 0b00100000;

    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // set alert bit as 1
    value[0] &= 0b11011111;
    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // clear alert bit

    BmsDeviceWriter::bmsDeviceWrite(device_address, ALERT_STATUS, 0xFF);  // write 1's to ALERT_STATUS_REG register
    BmsDeviceWriter::bmsDeviceWrite(device_address, ALERT_STATUS, 0x00);  // Write 0's ALERT_STATUS_REG register
}

void BmsDevice::clearFaultsOnBmsDevice(byte
device_address) {
byte *value = BmsDeviceReader::bmsDeviceRead(device_address, DEVICE_STATUS,
                                             1);  // clear alert bit in device status register
    value[0] |= 0b01000000;

    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // set alert bit as 1
    value[0] &= 0b10111111;
    BmsDeviceWriter::writeStatusOfBmsDevice(device_address, value[0]);  // clear alert bit

    BmsDeviceWriter::bmsDeviceWrite(device_address, FAULT_STATUS, 0xFF);  // write 1's to ALERT_STATUS_REG register
    BmsDeviceWriter::bmsDeviceWrite(device_address, FAULT_STATUS, 0x00);  // write 0's ALERT_STATUS_REG register
}
