/**
* File: patchugino_analog.h
* Created on: 2025-08-04 at 13:31
* Author: Andrea Rantin
* Description: This file contains the class Patchugino_Analog that is the class used for
* managing the Patchugino_Analog board. It allows to initialize the board with the specified I2C address and read any
* of the 4 provided channels either as input Voltage or Current
*/

#pragma once

#include "patchugo_core.h"
#include "internal/patchugino_analog_types.h"
#include <Wire.h>

using namespace PatchuginoAnalog;

namespace PatchuginoAnalog {

    class Patchugino_Analog {
        private:
            int usedI2CAddr; /*<! I2C Address used for communication. Selected from H10 pin header*/
            Patchugo_Logger* logger = nullptr; /*<! Logger instance used for logging of this library*/
            static constexpr uint32_t ADC_MAX_VAL = 32768; /*<! Max value of ADC that can be read */
            static constexpr uint8_t CURRENT_RESISTANCE_DIV = 200; /*<! Value to use in division to get current */
            static constexpr float VOLTAGE_MUL = 2.5f; /*<! Value to use in multiplication to get voltage*/
            /**
            * @brief Configures the ADS1115 to read continuous conversion on the selected channel
            * 
            * @param channel Channel to configure and read
            * 
            * @return: //TODO
            */
            PatchugoStatusCode ADS1115_Config_ForRead(AnalogChannel channel);

            /**
            * @brief Converts a raw ADC reading to voltage
            * 
            * @param adcRawVal Value of ADC to convert
            * @return float Voltage value
            */
            float ADC_ToVoltage(uint16_t adcRawVal);

            /**
            * @brief Converts a raw ADC reading to current
            * 
            * @param adcRawVal Value of ADC to convert
            * @return float Current value
            */
            float ADC_ToCurrent(uint16_t adcRawVal);
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

            /**
            * @brief Reads the given analog channel and converts to either Voltage or Current depending on
            * the reading type
            * 
            * @param channel Channel to read
            * @param readType Reading type(Either Voltage or Current reading)
            * @return PatchugoStatusCode //TODO
            */
            PatchugoStatusCode Read(AnalogChannel channel, AnalogReadType readType, uint16_t* readAdc, float* readConv);
    };
}

