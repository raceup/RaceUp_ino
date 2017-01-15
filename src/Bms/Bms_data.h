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


#ifndef RACEUP_INO_CORE_BMS_DATA_H
#define RACEUP_INO_CORE_BMS_DATA_H

#include <Arduino.h>

#ifndef SLAVE_SELECT_PIN
#define SLAVE_SELECT_PIN 10  // pin 53 is reserved!
#endif

#ifndef ENABLE_CHARGER
#define ENABLE_CHARGER 5
#endif

#ifndef CHARGER_PIN
#define CHARGER_PIN 6
#endif

/**
 * This is the list of recognized commands. These can be commands that can either be sent or received.
 * In order to receive, attach a callback function to these events
 */
enum {
    kAcknowledge, // acknowledge that cmd was received
    kError, // report errors
    kStartLogging, // request logging start (typically PC -> Arduino)
    kPlotDataPoint, // request datapoint plotting (typically Arduino -> PC)
    kAlert,
    kFault,
    kStatus,
    kCellVoltage,
    kCellTemperature,
    kSleep
};

const byte DEVICE_STATUS = 0x00;  // arduino board pre-defined byte status
const byte GPAI = 0x01;
const byte TEMPERATURE1 = 0x0F;
const byte ALERT_STATUS = 0x20;
const byte FAULT_STATUS = 0x21;
const byte ADC_CONTROL = 0x30;
const byte IO_CONTROL = 0x31;
const byte CB_CTRL = 0x32;
const byte CB_TIME = 0x33;
const byte ADC_CONVERT = 0x34;
const byte SHDW_CTRL = 0x3A;
const byte ADDRESS_CONTROL = 0x3B;
const byte RESET = 0x3C;
const byte FUNCTION_CONFIG = 0x40;
const byte CONFIG_COV = 0x42;
const byte CONFIG_COVT = 0x43;
const byte CONFIG_CUV = 0x44;
const byte CONFIG_CUVT = 0x45;
const byte OV_THRESHOLD = 0x2c;  // -> 4.2V -> (4.2-2)/0.05 = 44 = 0x2c
const byte UV_THRESHOLD = 0x17;  // -> 3V -> (3-0.7)/0.1 = 23 = 0x17
const byte OV_TIMER = (const byte) true;  // (0x01 || 0x80) 100ms + MSB set to 1 for milliseconds -> 100 = 0x01 ; MSB 1 = 0x80
const byte UV_TIMER = (const byte) true;  // (0x01 || 0x80) 100ms + MSB set to 1 for milliseconds -> 100 = 0x01 ; MSB 1 = 0x80

#ifdef ARDUINO_DUE  // arduino DUE specifics
#define  CRUISE_EN 44
#define  CONV_PIN 9
#define  DRDY_PIN 10
#define  ALERT_PIN 11
#define  FAULT_PIN 8
#define  SLAVE_SELECT_PIN 12
#define  ENABLE_CHARGER 38
#define  CHARGER_PIN 36
#define  LED_PIN 13

const double OT_THRESHOLD = 0x55; // -> TS1=60C , TS2 =60C
const double OT_TIMER = 0x01;     // 10ms
#endif

#endif //RACEUP_INO_CORE_BMS_DATA_H
