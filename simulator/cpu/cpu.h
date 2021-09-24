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
  WORD A15 : 1;

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

  // Address Bus Write
  void output_A(WORD address) {

    for (int i = 0; i < 16; i++) {
        
      int value = (address >> i) & 0b0000000000000001;

      if (i == 0) A0 = value;
      else if (i == 1) A1 = value;
      else if (i == 2) A2 = value;
      else if (i == 3) A3 = value;
      else if (i == 4) A4 = value;
      else if (i == 5) A5 = value;
      else if (i == 6) A6 = value;
      else if (i == 7) A7 = value;
      else if (i == 8) A8 = value;
      else if (i == 9) A9 = value;
      else if (i == 10) A10 = value;
      else if (i == 11) A11 = value;
      else if (i == 12) A12 = value;
      else if (i == 13) A13 = value;
      else if (i == 14) A14 = value;
      else if (i == 15) A15 = value;

    }

    update_address_bus();
    
  }

  // Data Bus Read
  BYTE read_D () {

    setDataBus(1);
    update_data_bus();

    WORD data = 0;
  
    if (D0) data |= 0b00000001;
    if (D1) data |= 0b00000010;
    if (D2) data |= 0b00000100;
    if (D3) data |= 0b00001000;
    if (D4) data |= 0b00010000;
    if (D5) data |= 0b00100000;
    if (D6) data |= 0b01000000;
    if (D7) data |= 0b10000000;

    return data;
    
  }

  // Data Bus Write
  void output_D (BYTE data) {

    for (int i = 0; i < 8; i++) {
        
      int value = (data >> i) & 0b00000001;

      if (i == 0) D0 = value;
      else if (i == 1) D1 = value;
      else if (i == 2) D2 = value;
      else if (i == 3) D3 = value;
      else if (i == 4) D4 = value;
      else if (i == 5) D5 = value;
      else if (i == 6) D6 = value;
      else if (i == 7) D7 = value;

    }

    setDataBus(0);
    update_data_bus();

  }

  // Read from Address
  BYTE read (WORD address) {

    // Set RWB to R state
    RWB = HIGH;
    update_general_outputs();

    // Output address in address bus
    output_A(address);

    delay(50);

    // Read address from data bus
    return read_D();
    
  }

  // Reset Sequence (7 clock cicles)
  void reset() {

    //...
    // Load ProgramCounter
    BYTE least = read(0xFFFC);
    BYTE most = read(0xFFFD);
    PC = 0;
    PC |= most;
    PC <<= 8;
    PC |= least;

  }

  // Debug (Serial)
  void debug() {
    
    // Program Counter
    Serial.print(PC, HEX);

    Serial.print("  ");
    
    // Address bus
    A15 ? Serial.print("1") : Serial.print("0");
    A14 ? Serial.print("1") : Serial.print("0");
    A13 ? Serial.print("1") : Serial.print("0");
    A12 ? Serial.print("1") : Serial.print("0");
    A11 ? Serial.print("1") : Serial.print("0");
    A10 ? Serial.print("1") : Serial.print("0");
    A9 ? Serial.print("1") : Serial.print("0");
    A8 ? Serial.print("1") : Serial.print("0");
    A7 ? Serial.print("1") : Serial.print("0");
    A6 ? Serial.print("1") : Serial.print("0");
    A5 ? Serial.print("1") : Serial.print("0");
    A4 ? Serial.print("1") : Serial.print("0");
    A3 ? Serial.print("1") : Serial.print("0");
    A2 ? Serial.print("1") : Serial.print("0");
    A1 ? Serial.print("1") : Serial.print("0");
    A0 ? Serial.print("1") : Serial.print("0");

    Serial.print("    ");

    // RWB
    RWB ? Serial.print("R") : Serial.print("W");

    Serial.print("    ");
    
    // Data bus
    D7 ? Serial.print("1") : Serial.print("0");
    D6 ? Serial.print("1") : Serial.print("0");
    D5 ? Serial.print("1") : Serial.print("0");
    D4 ? Serial.print("1") : Serial.print("0");
    D3 ? Serial.print("1") : Serial.print("0");
    D2 ? Serial.print("1") : Serial.print("0");
    D1 ? Serial.print("1") : Serial.print("0");
    D0 ? Serial.print("1") : Serial.print("0");

    Serial.println("");
  }

  // Clock check variables
  int last_clock = 0;
  int cycles = 0;
  //int clock_change;

  // Main CPU loop
  void mainloop() {

    // Update clock variables
    //clock_change = !(last_clock == PHI2);
    if(!PHI2 && last_clock) {
      cycles++;
    }
    last_clock = PHI2;

    // Check RDY pin
    if (RDY) {

      /*
       * The processor counts a cycle every time
       * the previous iteration of mainloop PHI2
       * was high and now it's low.
       */
      if (cycles) {
        cycles--;

        // Reset signal check
        if (!RESB) {

          reset();

        }

        // Debug
        debug();


      }

    }

  }

};

