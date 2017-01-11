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


#include "BmsDeviceSetup.h"

void BmsDeviceSetup::CovCuvSetup(byte device_address) {
    BmsDeviceWriter::bmsDeviceWrite(device_address, SHDW_CTRL, 0x35);
    BmsDeviceWriter::bmsDeviceWrite(device_address, CONFIG_COV, OV_THRESHOLD);
    BmsDeviceWriter::bmsDeviceWrite(device_address, SHDW_CTRL, 0x35);
    BmsDeviceWriter::bmsDeviceWrite(device_address, CONFIG_COVT, OV_TIMER);

    BmsDeviceWriter::bmsDeviceWrite(device_address, SHDW_CTRL, 0x35);
    BmsDeviceWriter::bmsDeviceWrite(device_address, CONFIG_CUV, UV_THRESHOLD);
    BmsDeviceWriter::bmsDeviceWrite(device_address, SHDW_CTRL, 0x35);
    BmsDeviceWriter::bmsDeviceWrite(device_address, CONFIG_CUVT, UV_TIMER);
}

void BmsDeviceSetup::setAddresses() {
    for (byte n = 1; n <= NUMBER_OF_BMS_DEVICES; n++) {
        byte devAddress = n;
        BmsDeviceWriter::bmsDeviceWrite(0x00, ADDRESS_CONTROL, devAddress);
        CovCuvSetup(devAddress);
        BmsDevice::clearAlertsOnBmsDevice(devAddress);
        BmsDevice::clearFaultsOnBmsDevice(devAddress);
        delay(ONE_CENTSECOND);
    }
}

void BmsDeviceSetup::resetDevices() {
    BmsDeviceWriter::bmsDeviceWrite(0x3F, RESET, 0xA5);  // write reset code to reset register
}

void BmsDeviceSetup::setupBmsDevice(byte n, byte adc_control, byte function_config) {
    BmsDeviceWriter::bmsDeviceWrite(n, ADC_CONTROL, adc_control);  // gpai on, measure 1 to 5 cells
    BmsDeviceWriter::bmsDeviceWrite(n, SHDW_CTRL, 0x35);
    BmsDeviceWriter::bmsDeviceWrite(n, FUNCTION_CONFIG, function_config);  // gai measure 6 cells series on vbat to vss
}

void BmsDeviceSetup::setupBmsDevice(byte n) {
    if (n == 1 || n == 21) {  // one segment with one less cell voltage to read
        setupBmsDevice(n, 0b01111100, 0b01110100);
    } else {
        setupBmsDevice(n, 0b01111101, 0b01110000);
    }
}
