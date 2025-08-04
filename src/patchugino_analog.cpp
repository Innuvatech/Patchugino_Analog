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
    usedI2CAddr = static_cast<uint32_t>(i2cAddr);

    logger->Log_Verbose("Using I2C Addr: %ld\n", usedI2CAddr);
    
    Wire.end();
    Wire.begin();

    logger->Log_Info("Patchugino Analog initialized\n");
}