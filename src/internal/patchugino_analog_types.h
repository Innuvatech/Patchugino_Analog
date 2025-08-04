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
    * If the H10 jumper is set to GND then the address is (0x48).
    * If the H10 jumper is set to 5V then the address is (0x49).
    */
    enum class PatchuginoAnalogI2CAddr {
        I2C_ADDR_1 = (0x48U), /*<! H10 Jumper to GND*/
        I2C_ADDR_2 = (0x49U), /*<! H10 Jumper to 5V*/
    };

    //Utility constant expressions to ease use of enum class of PatchuginoAnalogI2CAddr
    static constexpr PatchuginoAnalogI2CAddr PATCHUGINO_ANALOG_ADDR_1 = PatchuginoAnalogI2CAddr::I2C_ADDR_1;
    static constexpr PatchuginoAnalogI2CAddr PATCHUGINO_ANALOG_ADDR_2 = PatchuginoAnalogI2CAddr::I2C_ADDR_2;

    /**
    * @brief Registers of ADS1115
    * 
    */
    enum class ADS1115Reg {
        CONV_REG = 0x00U,
        CONFIG_REG = 0x01U,
        LO_THRESH_REG = 0x02U,
        HI_THRESH_REG = 0x03U,
    };

    //Utility constant expressions to ease use of enum class of ADS1115Reg
    static constexpr ADS1115Reg ADS1115_CONV_REG = ADS1115Reg::CONV_REG;
    static constexpr ADS1115Reg ADS1115_CONFIG_REG = ADS1115Reg::CONFIG_REG;
    static constexpr ADS1115Reg ADS1115_LO_THRESH_REG = ADS1115Reg::LO_THRESH_REG;
    static constexpr ADS1115Reg ADS1115_HI_THRESH_REG = ADS1115Reg::HI_THRESH_REG;

    /**
    * @brief ADS1115 Comparator queue and disable. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115CompQue {
        COMP_QUE_ONE_CONV = (0x00U << 0), /*<! Assert after one conversion */
        COMP_QUE_TWO_CONV = (0x01U << 0), /*<! Asseert after two conversions */
        COMP_QUE_FOUR_CONV = (0X02U << 0), /*!< Assert after four conversions */
        COMP_QUE_DISABLE = (0x03U << 0), /*!< Disable comparator and set ALERT/RDY to high-impedance(default)*/
    };

    //Utility constant expressions to ease use of enum class of ADS1115CompQue
    static constexpr ADS1115CompQue ADS1115_COMP_QUE_ONE_CONV = ADS1115CompQue::COMP_QUE_ONE_CONV;
    static constexpr ADS1115CompQue ADS1115_COMP_QUE_TWO_CONV = ADS1115CompQue::COMP_QUE_TWO_CONV;
    static constexpr ADS1115CompQue ADS1115_COMP_QUE_FOUR_CONV = ADS1115CompQue::COMP_QUE_FOUR_CONV;
    static constexpr ADS1115CompQue ADS1115_COMP_QUE_DISABLE = ADS1115CompQue::COMP_QUE_DISABLE;

    /**
    * @brief ADS1115 Latching comparator. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115CompLat {
        NON_LATCHING = (0x00U << 2), /*!< Nonlatching comparator(default)*/
        LATCHING = (0x01U << 2), /*!< Latching comparator*/
    };

    //Utility constant expressions to ease use of enum class of ADS1115CompLat
    static constexpr ADS1115CompLat ADS1115_COMP_NON_LATCHING = ADS1115CompLat::NON_LATCHING;
    static constexpr ADS1115CompLat ADS1115_COMP_LATCHING = ADS1115CompLat::LATCHING;

    /**
    * @brief ADS1115 Comparator polarity. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115CompPol {
        ACTIVE_LOW = (0x00U << 3), /*!< Active low(default) */
        ACTIVE_HIGH = (0x01U << 3), /*!< Active high */
    };

    //Utility constant expressions to ease use of enum class of ADS1115CompPol
    static constexpr ADS1115CompPol ADS1115_COMP_POLARITY_LOW = ADS1115CompPol::ACTIVE_LOW;
    static constexpr ADS1115CompPol ADS1115_COMP_POLARITY_HIGH = ADS1115CompPol::ACTIVE_HIGH;

    /**
    * @brief ADS1115 Comparator mode. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115CompMode {
        TRADITIONAL = (0x00U << 4), /*!< Traditional comparator(default) */
        WINDOW = (0x01U << 4), /*!< Window comparator */
    };

    //Utility constant expressions to ease use of enum class of ADS1115CompMode
    static constexpr ADS1115CompMode ADS1115_COMP_MODE_TRADITIONAL = ADS1115CompMode::TRADITIONAL;
    static constexpr ADS1115CompMode ADS1115_COMP_MODE_WINDOW = ADS1115CompMode::WINDOW;

    /**
    * @brief ADS1115 Data rate. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115DR{
        DATA_RATE_8 = (0x00U << 5), /*!< 8SPS */
        DATA_RATE_16 = (0x01U << 5), /*!< 16SPS */
        DATA_RATE_32 = (0x02U << 5), /*!< 32SPS */
        DATA_RATE_64 = (0x03U << 5), /*!< 64SPS */
        DATA_RATE_128 = (0x04U << 5), /*!< 128SPS(default) */
        DATA_RATE_250 = (0x05U << 5), /*!< 250SPS */
        DATA_RATE_475 = (0x06U << 5), /*!< 475SPS */
        DATA_RATE_860 = (0x07U << 5), /*!< 860SPS */
    };

    //Utility constant expressions to ease use of enum class of ADS1115DR
    static constexpr ADS1115DR ADS1115_DATA_RATE_8 = ADS1115DR::DATA_RATE_8;
    static constexpr ADS1115DR ADS1115_DATA_RATE_16 = ADS1115DR::DATA_RATE_16;
    static constexpr ADS1115DR ADS1115_DATA_RATE_32 = ADS1115DR::DATA_RATE_32;
    static constexpr ADS1115DR ADS1115_DATA_RATE_64 = ADS1115DR::DATA_RATE_64;
    static constexpr ADS1115DR ADS1115_DATA_RATE_128 = ADS1115DR::DATA_RATE_128;
    static constexpr ADS1115DR ADS1115_DATA_RATE_250 = ADS1115DR::DATA_RATE_250;
    static constexpr ADS1115DR ADS1115_DATA_RATE_475 = ADS1115DR::DATA_RATE_475;
    static constexpr ADS1115DR ADS1115_DATA_RATE_860 = ADS1115DR::DATA_RATE_860;

    /**
    * @brief ADS1115 Operating mode. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115Mode {
        CONTINUOUS_CONV = (0x00U << 8), /*!< Continuous conversion mode*/
        SINGLE_SHOT = (0x01U << 8), /*!< Single-shot mode(default)*/
    };

    //Utility constant expressions to ease use of enum class of ADS1115Mode
    static constexpr ADS1115Mode ADS1115_MODE_CONTINUOUS_CONV = ADS1115Mode::CONTINUOUS_CONV;
    static constexpr ADS1115Mode ADS1115_MODE_SINGLE_SHOT = ADS1115Mode::SINGLE_SHOT;

    /**
    * @brief ADS1115 Programmable gain amplifier. For more info
    * consult datasheet at page 26
    */
    enum class ADS1115PGA {
        FSR_6144 = (0x00U << 9), /*!< FSR +- 6.144V */
        FSR_4096 = (0x01U << 9), /*!< FSR +- 4.096 */
        FSR_2048 = (0x02U << 9), /*!< FSR +- 2.048V(default) */
        FSR_1024 = (0x03U << 9), /*!< FSR +- 1.024V */
        FSR_0512 = (0x04U << 9), /*!< FSR +- 0.512V */
        FSR_0256 = (0x05U << 9), /*!< FSR +- 0.256V */
    };

    //Utility constant expressions to ease use of enum class of ADS1115PGA
    static constexpr ADS1115PGA ADS1115_PGA_6144 = ADS1115PGA::FSR_6144;
    static constexpr ADS1115PGA ADS1115_PGA_4096 = ADS1115PGA::FSR_4096;
    static constexpr ADS1115PGA ADS1115_PGA_2048 = ADS1115PGA::FSR_2048;
    static constexpr ADS1115PGA ADS1115_PGA_1024 = ADS1115PGA::FSR_1024;
    static constexpr ADS1115PGA ADS1115_PGA_0512 = ADS1115PGA::FSR_0512;
    static constexpr ADS1115PGA ADS1115_PGA_0256 = ADS1115PGA::FSR_0256;

    /**
    * @brief Channel to read of ADS1115
    * 
    */
    enum class AnalogChannel {
        IN0 = (0x04U << 12),
        IN1 = (0x05U << 12),
        IN2 = (0x06U << 12),
        IN3 = (0x07U << 12),
    };

    //Utility constant expressions to ease use of enum class of ADS1115Channel
    static constexpr AnalogChannel ANALOG_CHANNEL_0 = AnalogChannel::IN0;
    static constexpr AnalogChannel ANALOG_CHANNEL_1 = AnalogChannel::IN1;
    static constexpr AnalogChannel ANALOG_CHANNEL_2 = AnalogChannel::IN2;
    static constexpr AnalogChannel ANALOG_CHANNEL_3 = AnalogChannel::IN3;

    /**
    * @brief Type of analog reading(can be Voltage or Current reading)
    * 
    */
    enum class AnalogReadType {
        VOLTAGE_READING,
        CURRENT_READING,
    };

    //Utility constant expressions to ease use of enum class of AnalogReadType
    static constexpr AnalogReadType ANALOG_VOLTAGE_READING = AnalogReadType::VOLTAGE_READING;
    static constexpr AnalogReadType ANALOG_CURRENT_READING = AnalogReadType::CURRENT_READING;
}

