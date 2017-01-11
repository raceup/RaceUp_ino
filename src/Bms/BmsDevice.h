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

/**
 * Manages a BMS device
 */
class BmsDevice {

public:

    /**
     * Send alert on behalf of this bms
     * @param device_address address bms of bms to setup
     */
    static void clearAlertsOnBmsDevice(byte device_address);

    /**
     * Send fault on behalf of this device
     * @param device_address address bms of bms to setup
     */
    static void clearFaultsOnBmsDevice(byte device_address);
};


#endif //RACEUP_INO_CORE_BMSDEVICE_H
