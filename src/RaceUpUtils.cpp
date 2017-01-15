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


#include "RaceUpUtils.h"

const double RaceUpUtils::CELSIUS_TO_KELVIN_FACTOR = -273.15;
const double RaceUpUtils::BMS_VOLTAGE_RATIO_FACTOR = 6250.0 / 16383.0;

double RaceUpUtils::convertCellVoltage(double cellVoltageInt) {
    return cellVoltageInt * BMS_VOLTAGE_RATIO_FACTOR;
}

double RaceUpUtils::fromKelvinToCelsius(double kelvinValue) {
    return kelvinValue + CELSIUS_TO_KELVIN_FACTOR;
}

String RaceUpUtils::getArduinoBoardModelName() {
    ArduinoBoardManager arduinoBoardManager = ArduinoBoardManager();
    return arduinoBoardManager.BOARD_NAME;
}

bool RaceUpUtils::isArduinoUnoBoard() {
    return getArduinoBoardModelName() == "UNO";
}

bool RaceUpUtils::isArduinoDueBoard() {
    return getArduinoBoardModelName() == "DUE";
}
