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


#include "Utils.h"

const double Utils::CELSIUS_TO_KELVIN_FACTOR = -273.15;
const double Utils::BMS_VOLTAGE_RATIO_FACTOR = 6250.0 / 16383.0;

double Utils::convertCellVoltage(double cellVoltageInt) {
    return cellVoltageInt * BMS_VOLTAGE_RATIO_FACTOR;
}

double Utils::fromKelvinToCelsius(double kelvinValue) {
    return kelvinValue + CELSIUS_TO_KELVIN_FACTOR;
}

#ifdef ARDUINO_DUE
void Utils::frameToFloat(CAN_FRAME &frame, float *x, float *x1) {
    char vBuffer[4], vBuffer1[4];  // buffers to get frame value

    for (int count = 0; count < 8; count++) {
        if (count < 4) {
            vBuffer[count] = (char) frame.data.bytes[count];  // store first array
        } else {
            vBuffer1[count - 4] = (char) frame.data.bytes[count];  // store second array
        }
    }

    *x = *(float *) &vBuffer;
    *x1 = *(float *) &vBuffer1;
}

void Utils::frameToFloat(CAN_FRAME &frame, float *x) {
    char vBuffer[4];
    for (int count = 0; count < 4; count++) {
        vBuffer[count] = (char) frame.data.bytes[count];
    }

    *x = *(float *) &vBuffer;
}
#endif
