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


#ifndef BMS_SETUP_H
#define BMS_SETUP_H

#include <SPI.h>
#include <RaceUp_ino_core.h>

class BmsDeviceSetup {

public:

    /**
     * Setup a selected bms
     * @param device_address address bms of bms to setup
     */
    static void CovCuvSetup(byte device_address);

    /**
     * Set addresses in bms devices
     */
    static void setAddresses();

    /**
     * Reset all devices
     * @return reset all bms devices (including dev address)
     */
    static void resetDevices();

    /**
     * Setup bmsDevice device with parameters
     * @param n number of device
     * @param adc_control value of ADC_CONTROL to write
     * @param function_config value of FUNCTION_CONFIG to write
     */
    static void setupBmsDevice(byte n, byte adc_control, byte function_config);

    /**
     * Setup bmsDevice device
     * @param n number of device
     */
    static void setupBmsDevice(byte n);
};


#endif //BMS_SETUP_H
