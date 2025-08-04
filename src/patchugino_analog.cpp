/**
* File: patchugino_analog.cpp
* Created on: 2025-08-04 at 13:49
* Author: Andrea Rantin
* Description: Implementation file for patchugino_analog.h
*/

#include "patchugino_analog.h"

void Patchugino_Analog::Init(PatchuginoAnalogI2CAddr i2cAddr, HardwareSerial& serial, PatchugoLogLevel logLevel) {

    //Initialize logger
    static Patchugo_Logger localLogger(serial, logLevel);
    logger = &localLogger;

    logger->Log_Info("Patchugino Analog initializing\n");

    //Set I2C address used for communication with ADS1115
    usedI2CAddr = static_cast<int>(i2cAddr);

    logger->Log_Verbose("Using I2C Addr: %ld\n", usedI2CAddr);
    
    Wire.end();
    Wire.begin();

    logger->Log_Info("Patchugino Analog initialized\n");
}

float Patchugino_Analog::ADC_ToVoltage(uint16_t adcRawVal) {
    float voltage = 0.0f;
    voltage = ((float)adcRawVal / ADC_MAX_VAL) * 6.144;
    voltage *= VOLTAGE_MUL;
    //logger->Log_Debug("Converted voltage: %.2f\n", voltage);
    return voltage;
}

float Patchugino_Analog::ADC_ToCurrent(uint16_t adcRawVal) {
    float voltage = 0.0f;
    float current = 0.0f;
    voltage = (adcRawVal / ADC_MAX_VAL) * 6.144;
    current = (voltage / CURRENT_RESISTANCE_DIV) * 1000;
    //logger->Log_Debug("Converted current: %.2f\n", current);
    return current;
}

PatchugoStatusCode Patchugino_Analog::ADS1115_Config_ForRead(AnalogChannel channel) {
    logger->Log_Info("Configuring ADS1115 for read\n");

    uint16_t configReg = 0;

    configReg |= static_cast<uint32_t>(ADS1115_COMP_QUE_DISABLE);
    configReg |= static_cast<uint32_t>(ADS1115_COMP_NON_LATCHING);
    configReg |= static_cast<uint32_t>(ADS1115_COMP_POLARITY_LOW);
    configReg |= static_cast<uint32_t>(ADS1115_COMP_MODE_TRADITIONAL);
    configReg |= static_cast<uint32_t>(ADS1115_DATA_RATE_128);
    configReg |= static_cast<uint32_t>(ADS1115_MODE_CONTINUOUS_CONV);
    configReg |= static_cast<uint32_t>(ADS1115_PGA_6144);
    configReg |= static_cast<uint32_t>(channel);

    uint8_t configBuf[2] = {0};
    configBuf[0] = (uint8_t)(configReg >> 8) & 0xFF;
    configBuf[1] = (uint8_t) configReg & 0xFF;

    Wire.beginTransmission(usedI2CAddr);
    Wire.write(static_cast<uint8_t>(ADS1115_CONFIG_REG));
    Wire.write(configBuf, 2);

    if(Wire.endTransmission(true) != 0) return ERROR_ANALOG_WRITE_CONF_REG;

    delay(10);

    Wire.beginTransmission(usedI2CAddr);
    Wire.write(static_cast<uint8_t>(ADS1115_CONFIG_REG));
    if(Wire.endTransmission(false) != 0) return ERROR_ANALOG_WRITE_CONF_REG;

    Wire.requestFrom(usedI2CAddr, 2);
    uint8_t readBuf[2] = {0};
    if(Wire.available() != 2) return ERROR_ANALOG_READ_CONF_REG;

    readBuf[0] = Wire.read();
    readBuf[1] = Wire.read();

    uint16_t readConf = (readBuf[0] << 8) | readBuf[1];

    if(readConf != configReg) return ERROR_ANALOG_WRONG_CONF;

    Wire.endTransmission();

    return OK;
}

PatchugoStatusCode Patchugino_Analog::Read(AnalogChannel channel, AnalogReadType readType, uint16_t* readAdc, float* readConv) {

    PatchugoStatusCode checkError = ADS1115_Config_ForRead(channel);
    if(checkError != OK) return checkError;

    delay(10);

    Wire.beginTransmission(usedI2CAddr);
    Wire.write(static_cast<uint8_t>(ADS1115_CONV_REG));
    if(Wire.endTransmission(false) != 0) return ERROR_ANALOG_READ_CONV;

    Wire.requestFrom(usedI2CAddr, 2);
    uint8_t readBuf[2] = {0};
    if(Wire.available() != 2) return ERROR_ANALOG_READ_CONV;
    readBuf[0] = Wire.read();
    readBuf[1] = Wire.read();

    uint16_t adcRawVal = (readBuf[0] << 8) | readBuf[1];
    *readAdc = adcRawVal;

    logger->Log_Debug("ADC RAW VALUE: %d\n", *readAdc);

    switch(readType) {
        case AnalogReadType::VOLTAGE_READING:
            *readConv = ADC_ToVoltage(adcRawVal);
            break;
        case AnalogReadType::CURRENT_READING:
            *readConv = ADC_ToCurrent(adcRawVal);
            break;
        default:
            break;
    }

    return OK;
}