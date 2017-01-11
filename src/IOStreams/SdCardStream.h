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


#ifndef DATALOGGER_SDCARDSTREAM_H
#define DATALOGGER_SDCARDSTREAM_H

#include <SD.h>
#include <WString.h>

/**
 * Read and write to/from SD card inserted in Arduino.
 */
class SdCardStream {

public:
    /**
     * Creats SD card stream with chip and file path
     * @param chipSelect sd selection pin
     * @return SD card stream
     */
    SdCardStream(const uint8_t chipSelect);

    /**
     * Initialize stream
     */
    bool setup();

    /**
     * Open current file as stream
     * @param filePath file to open
     * @param mode read or write
     */
    File open(const String &filePath, uint8_t mode);

    /**
     * Checks if file exists
     * @param filePath file to check
     * @return true iff file exists
     */
    static bool doesFileExists(String filePath);

private:
    const uint8_t chipSelect;  // sd selection pin
    String currentFile;  // current file opened in stream
};


#endif //DATALOGGER_SDCARDSTREAM_H
