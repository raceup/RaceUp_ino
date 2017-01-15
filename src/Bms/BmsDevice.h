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


#ifndef RACEUP_INO_CORE_BMSDEVICE_H
#define RACEUP_INO_CORE_BMSDEVICE_H

#include <Arduino.h>
#include <SPI.h>
#include <avr/pgmspace.h>

#include "../RaceUpUtils.h"
#include "../data.h"
#include "Bms_data.h"

/**
 * Manages a BMS device
 */
class BmsDevice {

public:

    /**
     * New bms device
     * @param device_address byte device_address
     * @return new bms device
     */
    BmsDevice(byte device_address);

    // getters

    /**
     * @param temperatureToRead which temperature to read
     * @return temperature of device
     */
    double getTemperature(byte temperatureToRead) const;

    /**
     * TODO: WTF??
     * @param dev TODO: WTF??
     * @return TODO: WTF??
     */
    double getGpaiVbatt(bool dev) const;

    /**
     * Return cell voltage
     * @param cellNumber cell number
     * @return cell voltage of cell in device
     */
    int getCellVoltage(byte cellNumber) const;

    /**
     * Read status
     * @return device status
     */
    byte *getStatus() const;

    // setters

    /**
     * Write status
     * @param value value to write
     */
    void setStatus(byte value) const;

    /**
     * Send alert on behalf of this bms
     */
    void clearAlerts() const;

    /**
     * Send fault on behalf of this device
     */
    void clearFaults() const;

    // i/o

    /**
     * Read data read from registers
     * @param regAddress  registry address
     * @param length length to read
     * @return data read from registers
     */
    byte *readRegister(byte regAddress, byte length) const;

    /**
     * Write a bmsDevice device property
     * @param regAddress registry address
     * @param regData registry data
     */
    void writeRegister(byte regAddress, byte regData) const;

private:
    byte device_address;  // address of device

    // Thermistor data
    static const double BETA_THERMISTOR;
    static const double RB_THERMISTOR;
    static const double RT_THERMISTOR;
    static const double R0_THERMISTOR;

    /**
    * TODO: WTF??
    * @param crcBuffer crc buffer to check for errors
    * @return TODO: WTF??
    */
    static byte pec(byte crcBuffer[]);
};


#endif //RACEUP_INO_CORE_BMSDEVICE_H
