/**
* File: patchugino_analog_types.h
* Created on: 2025-08-04 at 13:44
* Author: Andrea Rantin
* Description: This file contains definitions for the Patchugino_Analog library,
* such as register values definitions for ADS111x and jumper selections on
* the board
*/

#pragma once

#include <Arduino.h>

namespace PatchuginoAnalog {

    /**
    * @brief Possible I2C addresses to select.
    * If the H10 jumper is set to GND then the address is (0x48 << 1).
    * If the H10 jumper is set to 5V then the address is (0x49 << 1).
    */
    enum class PatchuginoAnalogI2CAddr {
        I2C_ADDR_1 = (0x48U << 1), /*<! H10 Jumper to GND*/
        I2C_ADDR_2 = (0x49U << 1), /*<! H10 Jumper to 5V*/
    };

    //Utility constant expressions to ease use of enum class of PatchuginoAnalogI2CAddr
    static constexpr PatchuginoAnalogI2CAddr PATCHUGINO_ANALOG_ADDR_1 = PatchuginoAnalogI2CAddr::I2C_ADDR_1;
    static constexpr PatchuginoAnalogI2CAddr PATCHUGINO_ANALOG_ADDR_2 = PatchuginoAnalogI2CAddr::I2C_ADDR_2;
}

