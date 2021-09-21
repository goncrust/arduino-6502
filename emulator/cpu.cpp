/*
 * arduino-6502 (https://github.com/goncrust/arduino-6502)
 * 
 * CPU Emulator.
 *
 * Copyright (c) 2021 by goncrust
 * Released under the GPL v3.0
 * https://github.com/goncrust/arduino-6502/blob/main/LICENSE
 */


#include <iostream>

#define LITTLE_ENDIAN

// ----------------------------  Defenitions ---------------------------------

/* OpCodes
 *
 *
 */


// Data Size
typedef unsigned char BYTE
typedef short WORD


class CPU {
private:

  // --------------------------------------------------------------------------

  // Zero page (256 bytes): ($0000-$00FF)
  // Stack (256 bytes): ($0100-$01FF)
  // Addresses of the non-maskable interrupt handler: ($FFFA/B)
  // Power/reset location: ($FFFC/D)
  // BRK/interrupt request handler: ($FFFE/F)

  // ------------------------------- Registers --------------------------------

  // http://www.obelisk.me.uk/6502/registers.html

  // Progam Counter
  WORD PC; // The value of program counter is modified automatically as instructions are executed.

  // Stack Pointer
  BYTE SP; // The CPU does not detect if the stack is overflowed by excessive pushing or pulling operations and will most likely result in the program crashing.

  // Accumulator
  BYTE A;

  // Index Register X
  /*
   * Most commonly used to hold counters or offsets for accessing memory.
   * The X register has one special function. It can be used to get a copy of the stack pointer or change its value.
   */
  BYTE X;

  // Index Register Y
  /*
   * Same as X Register but as no special function.
   */
  BYTE Y;

  // Processor Status
  //             7             6                     5                             4                3               2                 1             0
  BYTE P; // Negative (N)  Overflow (V)   User status or mode bit (unused)    Break Command     Decimal (D)   IRQB disable (I)     Zero (Z)    Carry (C)

public:

  // -------------------------------- PINS ------------------------------------

  // Address Bus
  WORD A0 : 1;
  WORD A1 : 1;
  WORD A2 : 1;
  WORD A3 : 1;
  WORD A4 : 1;
  WORD A5 : 1;
  WORD A6 : 1;
  WORD A7 : 1;
  WORD A8 : 1;
  WORD A9 : 1;
  WORD A10 : 1;
  WORD A11 : 1;
  WORD A12 : 1;
  WORD A13 : 1;
  WORD A14 : 1;

  // Data Bus
  BYTE D0 : 1;
  BYTE D1 : 1;
  BYTE D2 : 1;
  BYTE D3 : 1;
  BYTE D4 : 1;
  BYTE D5 : 1;
  BYTE D6 : 1;
  BYTE D7 : 1;

  // Bus Enable
  WORD BE : 1;

  // Interrupt Request
  WORD IRQB : 1;

  // Memory Lock
  WORD MLB : 1;

  // Non-Maskable Interrupt
  WORD NMIB : 1;

  // No Connect is not defined since this is an emulator and it's not needed.

  // Phase 2 In, Phase 2 Out and Phase 1 Out
  WORD PHI2 : 1;
  WORD PHI2O : 1;
  WORD PHI1O : 1;

  // Read/Write
  WORD RWB : 1;

  // Ready
  WORD RDY : 1;

  // Reset
  WORD RESB : 1;

  // Set Overflow
  WORD SOB : 1;

  // SYNChronize with OpCode fetch
  WORD SYNC : 1;

  // Power (VDD) and Ground (VSS) are not defined since this is an emulator.

  // Vector Pull
  WORD VPB : 1;

  // -------------------------------- FUNCTIONS ----------------------------------

  // Read from specified processor status flag
  int read_P(int bit) {
    return (P >> bit) & 0x00000001
  }

  // Write to specified processor status flag
  void write_P(int value, int bit) {
    int mask;
    if (value) {
      if (bit == 0) mask = 0x00000001;
      else if (bit == 1) mask = 0x00000010;
      else if (bit == 2) mask = 0x00000100;
      else if (bit == 3) mask = 0x00001000;
      else if (bit == 4) mask = 0x00010000;
      else if (bit == 5) mask = 0x00100000;
      else if (bit == 6) mask = 0x01000000;
      else if (bit == 7) mask = 0x10000000;

      P |= mask;
    } else {
      if (bit == 0) mask = 0x11111110;
      else if (bit == 1) mask = 0x11111101;
      else if (bit == 2) mask = 0x11111011;
      else if (bit == 3) mask = 0x11110111;
      else if (bit == 4) mask = 0x11101111;
      else if (bit == 5) mask = 0x11011111;
      else if (bit == 6) mask = 0x10111111;
      else if (bit == 7) mask = 0x01111111;
    }

    P &= mask;
  }

  // Reset Sequence (7 clock cicle)
  void reset() {

    //...


  }

}



int main() {



}
