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


#ifndef RACEUP_INO_CORE_UTILS_H
#define RACEUP_INO_CORE_UTILS_H

#include <Arduino.h>
#include <due_can.h>

class Utils {

public:

    /**
     * Convert kelving temperature degree to celsius ones
     * @param kelvinValue kelvin temperature
     * @return equivalent celsius temperature
     */
    static double fromKelvinToCelsius(double kelvinValue);

    /**
     * View datasheet
     * @param cellVoltageInt
     * @return cell voltage according to datasheet
     */
    static double convertCellVoltage(double cellVoltageInt);

    // TODO instead of CAN_FRAM& take a byte& input
    /**
    * Stores frame value in 2 buffers of 4 chars each
    * @param frame frame frame to convert
    * @param x first array of 4 char containing buffer value
    * @param x1 second array of 4 char containing buffer value
    */
    static void frameToFloat(CAN_FRAME &frame, float *x, float *x1);

    /**
     * Stores frame value in a buffer with 4 char
     * @param frame frame to convert
     * @param x array of 4 char containing buffer value
     */
    static void frameToFloat(CAN_FRAME &frame, float *x);

    static const double CELSIUS_TO_KELVIN_FACTOR;
    static const double BMS_VOLTAGE_RATIO_FACTOR;
};


#endif //RACEUP_INO_CORE_UTILS_H
