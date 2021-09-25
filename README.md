# arduino-6502

6502 emulator/simulator for Arduino

## List of contents

1. [Features](#Features)
1. [Info](#Info)
3. [Get Started](#Get-Started)
4. [License](#License)

## Features

- 6502 CPU Simulator with all registers, pins (appart from VDD, VSS and NC), instructions and processor status flags from the last version of the processor, the `W65C02S` (for Arduino Mega)
  - (Optional) RAM/ROM Simulator (for Arduino Uno), with only 11 address bus pins.
- 6502 CPU Emulator in C++ (without Arduino)

## Info

This project is still in development, many features are not yet implemented.

### 6502 CPU Simulator

- Arduino/6502 PIN table:

| Arduino PIN(s)                                                 | 6502 Function                        |
|----------------------------------------------------------------|--------------------------------------|
| 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53 | ADDRESS BUS (A0-A15)                 |
| 8                                                              | BUS ENABLE (BE)                      |
| 22, 24, 26, 28, 30, 32, 34, 36                                 | DATA BUS (D0-D7)                     |
| 3                                                              | INTERRUPT REQUEST (IRQB)             |
| 4                                                              | MEMORY LOCK (MLB)                    |
| 5                                                              | NON-MASKABLE INTERRUPT (NMIB)        |
| -                                                              | NO CONNECT (NC)                      |
| 9                                                              | PHASE 2 IN (PHI2)                    |
| 11                                                             | PHASE 2 OUT (PHI2O)                  |
| 2                                                              | PHASE 1 OUT (PHI1O)                  |
| 7                                                              | READ/WRITE (RWB)                     |
| A1                                                             | READY (RDY)                          |
| 12                                                             | RESET (RESB)                         |
| 10                                                             | SET OVERFLOW (SOB)                   |
| 6                                                              | SYNCHRONIZE WITH OPCODE FETCH (SYNC) |
| -                                                              | POWER (VDD) AND GROUND (VSS)         |
| A0                                                             | VECTOR PULL (VPB)                    |

### RAM/ROM Simulator

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
