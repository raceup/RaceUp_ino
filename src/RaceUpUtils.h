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
#include <ArduinoBoardManager.h>

class RaceUpUtils {

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

    /**
     * Checks if current board is an Arduino UNO
     * @return true iff current board is an Arduino UNO
     */
    static bool isArduinoUnoBoard();

    /**
     * Checks if current board is an Arduino DUE
     * @return true iff current board is an Arduino DUE
     */
    static bool isArduinoDueBoard();

    /**
     * Gets current board model name
     * @return current board model name
     */
    static String getArduinoBoardModelName();

    static const double CELSIUS_TO_KELVIN_FACTOR;
    static const double BMS_VOLTAGE_RATIO_FACTOR;
};


#endif //RACEUP_INO_CORE_UTILS_H
