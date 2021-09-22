# arduino-6502

6502 emulator/simulator for Arduino

## List of contents

1. [Info](#Info)
1. [Features](#Features)
1. [Get Started](#Get-Started)
1. [License](#License)

## Info

This project is still in development, many features are not yet implemented.

## Features

- 6502 CPU Simulator with all registers, pins (appart from VDD, VSS and NC), instructions and processor status flags from the last version of the processor, the `W65C02S` (for Arduino Mega)
  - (Optional) RAM/ROM Simulator (for Arduino Uno), with only 11 address bus pins.
- 6502 CPU Emulator in C++ (without Arduino)

## Get Started

- For the CPU/Memory Simulator (Arduino):
  1. Clone the repo
  1. Go into the directory `simulator` (`romram-sim` for memory)
  1. `arduino-cli board list` to get the port Arduino Mega (Uno for memory) is connected to
  1. `arduino-cli board attach [port]`
  1. `sudo make` to compile and upload the code to the Arduino.

- For CPU Emulator (Without Arduino):
  1. Clone the repo
  1. Go into the directory `emulator`
  1. Compile with `g++ cpu.cpp`

## License

The source code is licensed under the open source GPL v3.0. License is available [here](https://github.com/goncrust/arduino-6502/blob/main/LICENSE).
