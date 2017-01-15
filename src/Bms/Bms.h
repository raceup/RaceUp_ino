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


#ifndef RACEUP_INO_CORE_BMS_H
#define RACEUP_INO_CORE_BMS_H

#include "BmsDevice.h"
#include "Bms_data.h"

/**
 * Bms device on entire battery pack
 */
class Bms {
public:
    /**
     * New bms
     * @return new bms
     */
    Bms();

    // serial update

    /**
     * Send segment data
     * @param statusType String about type of status to broadcast
     * @param cell number of cell
     * @param segment number of segment
     * @param value value to send
     */
    template<class T>
    void sendSegmentStatus(String statusType, byte cell, byte segment, T value) const {
        Serial.print(F("{"));  // open JSON
        Serial.print(F("\""));
        Serial.print(F("type"));
        Serial.print("\":\"");
        Serial.print(statusType);
        Serial.print(F("\","));
        Serial.print(F("\""));
        Serial.print(F("cell"));
        Serial.print("\":\"");
        Serial.print(cell);
        Serial.print(F("\","));
        Serial.print(F("\""));
        Serial.print(F("segment"));
        Serial.print("\":\"");
        Serial.print(segment);
        Serial.print(F("\","));

        Serial.print(F("\""));
        Serial.print(F("value"));
        Serial.print(F("\":\""));
        Serial.print(value);
        Serial.print(F("\""));
        Serial.println(F("}"));  // close JSON
    }

    /**
     * Send data
     * @param sender Sender
     * @param typeValue Type of arg to send
     * @param value value to send
     */
    template<class T>
    void sendUpdate(byte typeValue, T value) const {
        sendSegmentStatus(commandToString(typeValue), (byte) - 1, (byte) - 1, value);
    }

    /**
     * Send status
     * @param sender Sender
     * @param value Status to send
     */
    template<class T>
    void sendStatus(T value) const {
        sendUpdate(kStatus, value);
    }

    /**
     * Send segment voltage data
     * @param sender Sender
     * @param cell Cell number
     * @param segment Segment number
     * @param segmentVoltage Voltage of segment in cell number
     * @param value value to send
     */
    void sendSegmentVoltage(byte cell, byte segment, double value);

    /**
     * Send voltage data on the pack of bmsDevice device
     * @param n bmsDevice device
     */
    void sendPackVoltageOfBmsDevice(byte n);

    /**
     * Send temperature data on the segment
     * @param sender Sender
     * @param cell Cell number
     * @param segment Segment number
     * @param segmentVoltage Temperature of segment in cell number
     * @param value value to send
     */
    void sendSegmentTemperature(byte cell, byte segment, double value);

    /**
     * Send temperature data on the pack of bmsDevice device
     * @param n bmsDevice device
     */
    void sendPackTemperatureOfBmsDevice(byte n);

    /**
     * Reads serial data and checks if there is an update coming from the client
     * @return Raw String read from serial
     */
    static String getSerialUpdate();

    /**
     * Translate enum command to a string
     * @param command command number (as from the previously defined enum)
     * @return string representing name of command
     */
    static String commandToString(int command);
};


#endif //RACEUP_INO_CORE_BMS_H
