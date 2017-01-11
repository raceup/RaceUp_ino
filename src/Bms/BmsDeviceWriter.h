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


#ifndef RACEUP_INO_CORE_BMSDEVICEWRITER_H
#define RACEUP_INO_CORE_BMSDEVICEWRITER_H

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "Bms_data.h"
#include "../data.h"

class BmsDeviceWriter {

public:

    /**
     * TODO: WTF??
     * @param crcBuffer crc buffer to check for errors
     * @return TODO: WTF??
     */
    static byte pec(byte crcBuffer[]);

    /**
     * Write a bmsDevice device property
     * @param deviceAddress where to write
     * @param regAddress registry address
     * @param regData registry data
     */
    static void bmsDeviceWrite(byte deviceAddress, byte regAddress, byte regData);

    /**
     * Write status
     * @param deviceAddress address of device to get info of
     * @param value value to write
     */
    static void writeStatusOfBmsDevice(byte device_address, byte value);
};


#endif //RACEUP_INO_CORE_BMSDEVICEWRITER_H
