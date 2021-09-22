/*
 * arduino-6502 (https://github.com/goncrust/arduino-6502)
 * 
 * CPU Emulator ready for Arduino.
 *
 * Copyright (c) 2021 by goncrust
 * Released under the GPL v3.0
 * https://github.com/goncrust/arduino-6502/blob/main/LICENSE
 */

//#include "pins.h"

#define USING_LITTLE_ENDIAN

// ----------------------------  Defenitions ---------------------------------

/* OpCodes
 *
 *
 */


// Data Size
typedef unsigned char BYTE;
typedef short WORD;


class CPU {
//private:
public:

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
  // Can't use SP as a name since it's reserved.
  BYTE SP_; // The CPU does not detect if the stack is overflowed by excessive pushing or pulling operations and will most likely result in the program crashing.

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

//public:

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
    return (P >> bit) & 0x00000001;
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

  // Address Bus
  void output_A(WORD address) {

    for (int i = 0; i < 16; i++) {
        
      int value = (address >> i) & 0b0000000000000001;

      if (i == 0) digitalWrite(A0P, value);
      else if (i == 1) digitalWrite(A1P, value);
      else if (i == 2) digitalWrite(A2P, value);
      else if (i == 3) digitalWrite(A3P, value);
      else if (i == 4) digitalWrite(A4P, value);
      else if (i == 5) digitalWrite(A5P, value);
      else if (i == 6) digitalWrite(A6P, value);
      else if (i == 7) digitalWrite(A7P, value);
      else if (i == 8) digitalWrite(A8P, value);
      else if (i == 9) digitalWrite(A9P, value);
      else if (i == 10) digitalWrite(A10P, value);
      else if (i == 11) digitalWrite(A11P, value);
      else if (i == 12) digitalWrite(A12P, value);
      else if (i == 13) digitalWrite(A13P, value);
      else if (i == 14) digitalWrite(A14P, value);
      else if (i == 15) digitalWrite(A15P, value);

    }
    
  }

  // Data Bus Read
  BYTE read_D () {

    WORD data = 0;
  
    if (digitalRead(D0P)) {
      data |= 0b00000001;
      } 
    if (digitalRead(D1P)) {
      data |= 0b00000010;
    } 
    if (digitalRead(D2P)) {
      data |= 0b00000100;
    } 
    if (digitalRead(D3P)) {
      data |= 0b00001000;
    } 
    if (digitalRead(D4P)) {
      data |= 0b00010000;
    } 
    if (digitalRead(D5P)) {
      data |= 0b00100000;
    } 
    if (digitalRead(D6P)) {
      data |= 0b01000000;
    } 
    if (digitalRead(D7P)) {
      data |= 0b10000000;
    } 

    return data;
    
  }

  // Data Bus Write
  void output_D (BYTE data) {

    for (int i = 0; i < 8; i++) {
        
      int value = (data >> i) & 0b00000001;

      if (i == 0) digitalWrite(D0P, value);
      else if (i == 1) digitalWrite(D0P, value);
      else if (i == 2) digitalWrite(D1P, value);
      else if (i == 3) digitalWrite(D2P, value);
      else if (i == 4) digitalWrite(D3P, value);
      else if (i == 5) digitalWrite(D4P, value);
      else if (i == 6) digitalWrite(D5P, value);
      else if (i == 7) digitalWrite(D6P, value);

    }

  }

  // Read from Address
  BYTE read (WORD address) {

    // Set RWB to R state
    digitalWrite(RWBP, HIGH);
    setDataBus(1);

    // Output address in address bus
    output_A(address);

    delay(50);

    // Read address from data bus
    return read_D();
    
  }

  // Reset Sequence (7 clock cicle)
  void reset() {

    Serial.print("reset");
    //...
    // Load ProgramCounter
    BYTE least = read(0xFFFC);
    BYTE most = read(0xFFFD);
    PC = 0;
    PC |= most;
    PC <<= 8;
    PC |= least;

  }

};

