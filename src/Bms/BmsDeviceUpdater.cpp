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


#include "BmsDeviceUpdater.h"

void BmsDeviceUpdater::sendSegmentVoltage(byte cell, byte segment, double value) {
    sendSegmentStatus(commandToString(kCellVoltage), cell, segment, value);
}

void BmsDeviceUpdater::sendPackVoltageOfBmsDevice(byte n) {
    byte segment = (n - 1) / 3;
    for (byte cell = 0; cell < 18; cell++) {  // loop through cells monitored by bms device (6 of them)
        sendSegmentVoltage(cell, segment, BmsDeviceReader::getCellVoltage(n, cell));  // send voltage
    }
}

void BmsDeviceUpdater::sendSegmentTemperature(byte cell, byte segment, double value) {
    sendSegmentStatus(commandToString(kCellTemperature), cell, segment, value);
}

void BmsDeviceUpdater::sendPackTemperatureOfBmsDevice(byte n) {
    byte segment = (n - 1) / 3;
    for (byte cell = 0; cell < 18; cell++) {  // loop through cells monitored by bms device (6 of them)
        double value = BmsDeviceReader::getTemperature(n, TEMPERATURE1);
        sendSegmentTemperature(cell, segment, value);
    }
}

String BmsDeviceUpdater::getSerialUpdate() {
    return Serial.readString();
}

String BmsDeviceUpdater::commandToString(int command) {
    switch (command) {
        case 0:
            return (String) "Acknowledge";
        case 1:
            return (String) "Error";
        case 2:
            return (String) "Log";
        case 3:
            return (String) "Plot";
        case 4:
            return (String) "Alert";
        case 5:
            return (String) "Fault";
        case 6:
            return (String) "Status";
        case 7:
            return (String) "Voltage";
        case 8:
            return (String) "Temperature";
        case 9:
            return (String) "Sleep";
        default:
            return (String) "Unknown";
    }
}
