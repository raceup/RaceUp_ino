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


#ifndef RACEUP_INO_CORE_BMSDEVICEREADER_H
#define RACEUP_INO_CORE_BMSDEVICEREADER_H

#include <Arduino.h>

#include "Bms_data.h"

class BmsDeviceReader {

public:
    /**
     * Read data read from registers
     * @param deviceAddress where to read
     * @param regAddress  registry address
     * @param length length to read
     * @return data read from registers
     */
    static byte *bmsDeviceRead(byte deviceAddress, byte regAddress, byte length);

    /**
     * @param device_address address of device
     * @param temperature registry address of temperature to read
     * @return temperature of device
     */
    static double getTemperature(byte device_address, byte temperature);

    /**
     * TODO: WTF??
     * @param device_address address of device
     * @param dev TODO: WTF??
     * @return TODO: WTF??
     */
    static double getGpaiVbatt(byte device_address, bool dev);

    /**
     * Return cell voltage
     * @param deviceAddress address of device to get info of
     * @param cellNumber cell number
     * @return cell voltage of cell in device
     */
    static int getCellVoltage(byte deviceAddress, byte cellNumber);

    /**
     * Read status
     * @param deviceAddress address of device to get info of
     */
    static byte *getBmsDeviceStatus(byte device_address);

    /**
     * Thermistor data
     */
    static const double BETA_THERMISTOR;
    static const double RB_THERMISTOR;
    static const double RT_THERMISTOR;
    static const double R0_THERMISTOR;
};


#endif //RACEUP_INO_CORE_BMSDEVICEREADER_H
