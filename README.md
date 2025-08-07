# Patchugino_Analog
Arduino library for Patchugino_Analog shield board

## Getting Started
This library allows to control the Patchugino_Analog shield board which can be mounted on top of a PatchugoLite board. It is therefore necessary to have
the Patchugo Boards package installed from [Arduino Boards Manager](https://docs.arduino.cc/learn/starting-guide/cores/). 

If you have not done that already, add this link in the "_Additional Boards Managers URLs_" in Arduino preferences:

https://github.com/Innuvatech/BoardManagerFiles/raw/main/package_innuvatech_index.json

## Board Description
The Patchugino_Analog board is a shield board that can be plugged on top of a PatchugoLite board. It allows to read up to 4 analog inputs that can be either 0-10V or 4-20mA.
Each input can be configured to read voltage or current with its corresponding pin header(H9, H1, H2, H3)

### Power Supply
This board needs to be powered from 24V on the CN8 connector. The 24V can be taked from The U23 connector of PatchugoLite or from an external source

### Sensor Connections
The board has 4 connectors for the 4 analog inputs(IN0, IN1, IN2, IN3). Depending on the selected jumpers of the corresponding pin header a voltage or current
reading on the input can be done. Below is the list of all possible configurations:

### 0-10V on IN0
  - Jumper on H9 to V0
### 4-20mA on IN0
  - Jumper on H9 to I0
### 0-10V on IN1
  - Jumper on H1 to V1
### 4-20mA to IN1
  - Jumper on H1 to I1
### 0-10V on IN2
  - Jumper on H2 to V2
### 4-20mA on IN2
  - Jumper on H2 to I2
### 0-10V on IN3
  -  Jumper on H3 to V3
### 4-20mA on IN3
  - Jumper on H3 to I3

## Library Usage
The arduino library allows to control the board in a really simple and intuitive way with just a few lines of code. It allows to initialize the board by specifying which I2C address is being used from H10. It allows to read any IN either as Voltage or Current input


### Initialization
The library provides an initialization function called **Init** that allows to initialize everything that the board needs in order to work. The function
takes the following parameters as input:
  -**i2cAddr**: The I2C address that has been selected from the pinheaders. The I2C addresses configuration can be seen down below
  - **serial(optional)**: This is an optional parameter. It specifies the Serial instance used by the internal logs of the library. If not provided this parameter      defaults to the default Serial instance of the PatchugoLite board
  - **logLevel(optional)**: This specifies the logging level of the library. Setting a higher logging level means more logs from the library will be shown. Logs from the library can be disabled by setting this to **LOG_LEVEL_NONE**. For more information about logging please consult the [Patchugo_Core](https://github.com/Innuvatech/Patchugo_Core) repository

#### I2C Addresses configuration table
| Definition name | H10 | I2C Address |
| ----------------| ----| ------------|
| PATCHUGINO_ANALOG_ADDR_1 | TO PGND | 0x48 |
| PATCHUGINO_ANALOG_ADDR_2 | TO 5V | 0x49 |

#### Minimal initialization

```
  /*
    IMPORTANT!!! Patchugino Analog library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);

  //Initialize the Analog shield board and specify which I2C address it's using(0x48 in this case)
  //Since serial and logLevel are not specified this will default to using Serial with LOG_LEVEL_VERBOSE
  patchuginoRelay.Init(PATCHUGINO_ANALOG_ADDR_1);
```

#### Custom logging initialization
```
  /*
    IMPORTANT!!! Patchugino Analog library needs
    Serial instance to be initialized before calling any function!
  */
  HardwareSerial mySerial(PA10, PA11);
  
  //Initialize the Analog shield board and specify which I2C address it's using(0x48 in this case)
  //This will use mySerial as logs output channel and will only show DEBUG level logs or lower
  patchuginoRelay.Init(PATCHUGINO_ANALOG_ADDR_1, mySerial, LOG_LEVEL_DEBUG);
```
#### No logging initialization
```
void setup() {
  /*
    IMPORTANT!!! Patchugino Analog library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);
  
  //Initialize the Analog shield board and specify which I2C address it's using(0x48 in this case)
  //This will disable logs of the library. A valid Serial instance still needs to be provided
   patchuginoRelay.Init(PATCHUGINO_ANALOG_ADDR_1, Serial, LOG_LEVEL_NONE);
```

### Reading
To read any of the inputs from the board a **Read** function is provided. The function takes the following parameters:
  - channel: Which input is being read(For example IN0 or IN1). The values assignable to this parameter are the following:
      - ANALOG_CHANNEL_0
      - ANALOG_CHANNEL_1
      - ANALOG_CHANNEL_2
      - ANALOG_CHANNEL_3
    - readType: What type of reading is being made(Voltage or Current reading). The values assignable to this parameter are the following:
      - ANALOG_VOLTAGE_READING
      - ANALOG_CURRENT_READING
    - readAdc: uint16_t pointer that will be filled with the raw ADC value that has been read
    - readConv: float pointer that will be filled with the Voltage read(if the selected type was a Voltage reading) or with the Current(if the selected type was a     current reading)
   
    Reading examples are provided below:
  ```
  //Reads the ADC raw value and voltage of IN0
  uint16_t rawAdcVal = 0;
  float voltageVal = 0.0f;
  patchuginoAnalog.Read(ANALOG_CHANNEL_0, ANALOG_VOLTAGE_READING, &rawAdcVal, &voltageVal);

  //Reads the ADC raw value and current of IN2
  uint16_t rawAdcVal2 = 0;
  float currentVal = 0.0f;
  patchuginoAnalog.Read(ANALOG_CHANNEL_2, ANALOG_CURRENT_READING, &rawAdcVal2, &currentVal);
 ```
