/**
* File: patchugino_analog.h
* Created on: 2025-08-04 at 13:31
* Author: Andrea Rantin
* Description: This file contains the class Patchugino_Analog that is the class used for
* managing the Patchugino_Analog board. It allows to initialize the board with the specified I2C address and read any
* of the 4 provided channels either as input Voltage or Current
*/

#include "patchugo_core.h"
#include "internal/patchugino_analog_types.h"
#include <Wire.h>

using namespace PatchuginoAnalog;

namespace PatchuginoAnalog {

    class Patchugino_Analog {
        private:
            uint32_t usedI2CAddr; /*<! I2C Address used for communication. Selected from H10 pin header*/
            Patchugo_Logger* logger = nullptr;
        public:
            /**
            * @brief Initializes the Patchugino_Analog board
            * 
            * @param i2cAddr I2C Address to use for the board(Selected from H10 pin header)
            * @param serial Serial used for logging of Patchugino_Analog. Defaults to Serial
            * @param logLevel Logging level used for logging of Patchugino_Analog. Defaults to LOG_LEVEL_VERBOSE
            * 
            * @note The serial instance must be initialized by calling Serial.begin before calling this Init function, otherwise logs
            * will not be visible!
            */
            void Init(PatchuginoAnalogI2CAddr i2cAddr, HardwareSerial& serial = Serial, PatchugoLogLevel logLevel = LOG_LEVEL_VERBOSE);
    };
}

