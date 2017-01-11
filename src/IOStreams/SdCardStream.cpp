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


#include "SdCardStream.h"

SdCardStream::SdCardStream(const uint8_t chipSelect) : chipSelect(chipSelect) {}

bool SdCardStream::doesFileExists(String filePath) {
    return SD.exists(filePath);
}

bool SdCardStream::setup() {
    return SD.begin(chipSelect);
}

File SdCardStream::open(const String &filePath, uint8_t mode) {
    return SD.open(filePath, mode);
}
