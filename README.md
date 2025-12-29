# tiny32_v3 🔧

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-3.18.2-blue.svg)](https://github.com/tenergyinnovation/tiny32_v3)
[![Platform](https://img.shields.io/badge/platform-ESP32-green.svg)](https://www.espressif.com/en/products/socs/esp32)

Arduino framework library for tiny32_v3 board - A powerful ESP32-based IoT development board with extensive sensor and module support.

## 📋 Table of Contents

- [Features](#features)
- [Hardware Specifications](#hardware-specifications)
- [Installed Libraries](#installed-libraries)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
- [Examples](#examples)
- [Support](#support)

## ✨ Features

- 🎯 **Hardware Abstraction Layer** for ESP32-based tiny32_v3 board
- 📡 **Modbus RTU** support for industrial sensors
- 🔌 **30+ Sensors/Modules** ready-to-use drivers
- ⚡ **PWM Control** with configurable frequency and resolution
- 🎛️ **GPIO Management** with built-in debouncing
- 🔊 **Buzzer Control** with beep patterns
- 💡 **LED Control** with blinking support
- 🔄 **Relay Control** for switching external devices
- 📊 **Power Meters** (PZEM-003, PZEM-016, SDM120CT, SDM630MCT)
- 🌡️ **Environmental Sensors** (Temperature, Humidity, Soil Moisture)
- 💨 **Wind Speed**, Solar Radiation, Water Flow sensors
- 🏭 **Industrial Modules** (Chillers, Inverters, PLCs)

## 🔧 Hardware Specifications

- **MCU**: ESP32 (240MHz, Dual-Core)
- **Memory**: 320KB RAM, 4MB Flash
- **GPIO**: Multiple digital I/O pins
- **Communication**:
  - RS485 (Modbus RTU) x2 ports
  - UART, I2C, SPI
  - WiFi, Bluetooth
- **Peripherals**:
  - 2x Push Buttons (SW1, SW2) with debouncing
  - 1x Slide Switch
  - 2x LEDs (Red, Blue)
  - 1x Relay
  - 1x Buzzer

## 📦 Installed Libraries

This library includes the following dependencies:

### 1. **Debounce Library** 🎯
- **Version**: Latest
- **Repository**: [wkoch/Debounce](https://github.com/wkoch/Debounce)
- **Location**: `src/Debounce/`
- **Purpose**: Software button debouncing for switches and buttons
- **Features**:
  - Configurable debounce delay (default: 50ms)
  - Edge detection (rising/falling)
  - Compatible with INPUT and INPUT_PULLUP modes
  - Low memory footprint
- **Usage in tiny32_v3**:
  - Integrated into `Sw1()` and `Sw2()` functions
  - Provides clean button press detection
  - Eliminates false triggers from mechanical bounce

## 🚀 Installation

### Automatic Installation

The library and its dependencies can be installed automatically using the provided scripts:

#### macOS/Linux:
```bash
cd lib
./clone_repo.sh
```

#### Windows:
```cmd
cd lib
clone_repo.bat
```

### Manual Installation

#### Method 1: Clone from GitHub

**macOS/Linux:**
```bash
# Clone tiny32_v3 library
git clone https://github.com/tenergyinnovation/tiny32_v3.git

# Clone Debounce library into tiny32_v3/src
cd tiny32_v3/src
git clone https://github.com/wkoch/Debounce.git
cd ../..
```

**Windows:**
```cmd
REM Clone tiny32_v3 library
git clone https://github.com/tenergyinnovation/tiny32_v3.git

REM Clone Debounce library into tiny32_v3\src
cd tiny32_v3\src
git clone https://github.com/wkoch/Debounce.git
cd ..\..
```

#### Method 2: Manual Download

1. Download **tiny32_v3** library:
   - Go to: https://github.com/tenergyinnovation/tiny32_v3
   - Click "Code" → "Download ZIP"
   - Extract to your `lib` folder

2. Download **Debounce** library:
   - Go to: https://github.com/wkoch/Debounce
   - Click "Code" → "Download ZIP"
   - Extract to `lib/tiny32_v3/src/Debounce/`

3. Verify structure:
```
lib/
└── tiny32_v3/
    ├── README.md
    ├── library.json
    ├── src/
    │   ├── tiny32_v3.h
    │   ├── tiny32_v3.cpp
    │   └── Debounce/
    │       ├── Debounce.h
    │       ├── Debounce.cpp
    │       └── ...
    └── examples/
```

## 🎯 Quick Start

### Basic Example

```cpp
#include <Arduino.h>
#include <tiny32_v3.h>

tiny32_v3 mcu;

void setup() {
  Serial.begin(115200);
  Serial.println("tiny32_v3 Starting...");
  
  mcu.buzzer_beep(2);  // Welcome beep
}

void loop() {
  // Edge detection - triggers once per button press
  if (mcu.Sw1()) {
    Serial.println("Button SW1 pressed!");
    mcu.BlueLED(true);
    mcu.buzzer_beep(1);
  }
  
  if (mcu.Sw2()) {
    Serial.println("Button SW2 pressed!");
    mcu.RedLED(true);
    mcu.buzzer_beep(2);
  }
  
  // Continuous read - true while button is held
  if (mcu.Sw1_read()) {
    Serial.println("SW1 is being held...");
  }
  
  delay(100);
}
```

### Button Debouncing Example

```cpp
// Edge detection (default behavior)
if (mcu.Sw1()) {
  // Triggers once when button is pressed
  // Perfect for counting button presses
}

// Continuous read
if (mcu.Sw1_read()) {
  // Returns true while button is held down
  // Perfect for hold-to-repeat actions
}
```

## 📚 API Reference

### Basic GPIO Functions

```cpp
void Relay(bool state);          // Control relay (true=ON, false=OFF)
void RedLED(bool state);         // Control red LED
void BlueLED(bool state);        // Control blue LED
void BuildinLED(bool state);     // Control built-in LED
void buzzer_beep(int times);     // Beep buzzer N times
```

### Button Functions (with Debouncing)

```cpp
bool Sw1(void);                  // Edge detection - triggers once per press
bool Sw2(void);                  // Edge detection - triggers once per press
bool Sw1_read(void);             // Continuous read - true while held
bool Sw2_read(void);             // Continuous read - true while held
bool Slid_sw(void);              // Read slide switch state
```

### LED Blinking

```cpp
void TickBlueLED(float seconds); // Blink blue LED (0=off, >0=blink interval)
void TickRedLED(float seconds);  // Blink red LED
void TickBuildinLED(float seconds); // Blink built-in LED
```

### PWM Control

```cpp
bool PWM_Setup(uint8_t channel, double freq, uint8_t resolution_bit, uint8_t pin);
bool PWM_Drive(uint8_t channel, uint8_t percentage);
bool Frequency_Out(uint8_t pin, double freq);
```

### Modbus RTU Sensors

```cpp
// Power Meters
bool PZEM_016(uint8_t id, float &volt, float &amp, ...);
bool PZEM_003(uint8_t id, float &volt, float &amp, ...);
float SDM120CT_Volt(uint8_t id);
float SDM630MCT_L1_Volt(uint8_t id);

// Environmental Sensors
bool WTR10_E(uint8_t id, float &temp, float &humi);
bool XY_MD02(uint8_t id, float &temp, float &humi);
float PR3000_H_N01_tempeature();

// And 30+ more sensors...
```

## 📖 Examples

The library includes extensive examples in the `examples/` folder:

- **Basic**: LED, Buzzer, Switch, Relay tests
- **PWM**: PWM control and frequency generation
- **Modbus RTU**: Reading sensors, searching addresses
- **OTA**: Over-the-air firmware updates
- **Advanced**: Modbus master/client implementations

## 🔧 Configuration

### PlatformIO Setup

Add to your `platformio.ini`:

```ini
[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = arduino
monitor_speed = 115200
lib_deps = 
    tiny32_v3
```

### Arduino IDE Setup

1. Install ESP32 board support
2. Copy `tiny32_v3` folder to Arduino `libraries` folder
3. Restart Arduino IDE
4. Select Board: "ESP32 Dev Module" or "NodeMCU-32S"

## 🐛 Troubleshooting

### Buttons Not Working Properly

If buttons trigger multiple times or don't work:
- ✅ Check that Debounce library is installed in `src/Debounce/`
- ✅ Use `Sw1()` / `Sw2()` for edge detection
- ✅ Use `Sw1_read()` / `Sw2_read()` for continuous reading
- ✅ Ensure proper wiring (buttons pull to GND when pressed)

### Compilation Errors

```
fatal error: Debounce/Debounce.h: No such file or directory
```

**Solution**: Install Debounce library following [Manual Installation](#manual-installation) steps.

### Modbus Communication Issues

- Check baud rate (default: 9600)
- Verify proper RS485 wiring
- Use search functions to find sensor addresses

## 📧 Support

- **Author**: Tenergy Innovation Co., Ltd.
- **Email**: uten.boonliam@tenergyinnovation.co.th
- **Website**: http://www.tenergyinnovation.co.th
- **Tel**: +66 89-140-7205
- **Repository**: https://github.com/tenergyinnovation/tiny32_v3

## 📄 License

MIT License - See LICENSE file for details

## 🙏 Credits

- **Debounce Library**: William Koch ([wkoch/Debounce](https://github.com/wkoch/Debounce))
- **ESP32 Framework**: Espressif Systems
- **Development**: Tenergy Innovation Team

---

**Version**: 3.18.2  
**Last Updated**: December 2025  
Made with 💙 by Tenergy Innovation Co., Ltd.
