/*
 * arduino-6502 (https://github.com/goncrust/arduino-6502)
 *
 * Arduino main functions.
 *
 * Copyright (c) 2021 by goncrust
 * Released under the GPL v3.0
 * https://github.com/goncrust/arduino-6502/blob/main/LICENSE
 */

void update_general_outputs();
void update_general_inputs();
void update_address_bus();
void update_data_bus();
void setDataBus(int mode);
//#include "cpu/pins.h"


// RIGHT
#define RWBP 7
// NC not used
#define BEP 8
#define PHI2P 9
#define SOBP 10
#define PHI2OP 11
#define RESBP 12
// VSS not used

// LEFT
#define VPBP 1
#define RDYP 2
#define PHI1OP 3
#define IRQBP 4
#define MLBP 5
#define NMIBP 6
#define SYNCP 7
// VDD not used

// DATA BUS
#define D0P 22
#define D1P 24
#define D2P 26
#define D3P 28
#define D4P 30
#define D5P 32
#define D6P 34
#define D7P 36

// ADDRESS BUS
#define A0P 23
#define A1P 25
#define A2P 27
#define A3P 29
#define A4P 31
#define A5P 33
#define A6P 35
#define A7P 37
#define A8P 39
#define A9P 41
#define A10P 43
#define A11P 45
#define A12P 47
#define A13P 49
#define A14P 51
#define A15P 53

#include "cpu/cpu.h"

/* Set Data Bus pin mode
 *  mode = 0 -> Output
 *  mode = 1 -> Input
 */
int dataBusMode;
void setDataBus(int mode) {

  dataBusMode = mode;

  if (mode) {
    pinMode(D0P, INPUT);
    pinMode(D1P, INPUT);
    pinMode(D2P, INPUT);
    pinMode(D3P, INPUT);
    pinMode(D4P, INPUT);
    pinMode(D5P, INPUT);
    pinMode(D6P, INPUT);
    pinMode(D7P, INPUT);
  } else {
    pinMode(D0P, OUTPUT);
    pinMode(D1P, OUTPUT);
    pinMode(D2P, OUTPUT);
    pinMode(D3P, OUTPUT);
    pinMode(D4P, OUTPUT);
    pinMode(D5P, OUTPUT);
    pinMode(D6P, OUTPUT);
    pinMode(D7P, OUTPUT);
  }

}


// CPU
CPU cpu;

void setup() {

  // Address Bus
  pinMode(A0P, OUTPUT);
  pinMode(A1P, OUTPUT);
  pinMode(A2P, OUTPUT);
  pinMode(A3P, OUTPUT);
  pinMode(A4P, OUTPUT);
  pinMode(A5P, OUTPUT);
  pinMode(A6P, OUTPUT);
  pinMode(A7P, OUTPUT);
  pinMode(A8P, OUTPUT);
  pinMode(A9P, OUTPUT);
  pinMode(A10P, OUTPUT);
  pinMode(A11P, OUTPUT);
  pinMode(A12P, OUTPUT);
  pinMode(A13P, OUTPUT);
  pinMode(A14P, OUTPUT);
  pinMode(A15P, OUTPUT);

  // Data Bus
  setDataBus(0);

  pinMode(BEP, INPUT); // if low, Address, Data and RWB should not be enabled
  pinMode(IRQBP, INPUT); // interrupt
  pinMode(MLBP, OUTPUT);
  pinMode(NMIBP, INPUT); // interrupt
  pinMode(PHI2P, INPUT); // clock
  pinMode(PHI2OP, OUTPUT);
  pinMode(PHI1OP, OUTPUT);
  pinMode(RWBP, OUTPUT); // high -> input from data bus, low -> output from data bus
  pinMode(RDYP, INPUT); // if low, halt the cpu
  pinMode(RESBP, INPUT); // reset
  pinMode(SOBP, INPUT); // if low set overflow bit (V) in the status code register (should not be used)
  pinMode(SYNCP, OUTPUT);
  pinMode(VPBP, OUTPUT);

  // PIN 13 as reset indicator
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);


  // Serial port
  Serial.begin(9600);
}

void update_general_outputs() {

  // Outputs
  digitalWrite(MLBP, cpu.BE);
  digitalWrite(PHI2OP, cpu.PHI2O);
  digitalWrite(PHI1OP, cpu.PHI1O);
  digitalWrite(RWBP, cpu.RWB);
  digitalWrite(SYNCP, cpu.SYNC);
  digitalWrite(VPBP, cpu.VPB);

}

void update_general_inputs() {

  // Inputs
  cpu.BE = digitalRead(BEP);
  cpu.IRQB = digitalRead(IRQBP);
  cpu.NMIB = digitalRead(NMIBP);
  cpu.PHI2 = digitalRead(PHI2P);
  cpu.RDY = digitalRead(RDYP);
  cpu.RESB = digitalRead(RESBP);
  cpu.SOB = digitalRead(SOBP);

  // Reset Indicator
  cpu.RESB ? digitalWrite(13, LOW) : digitalWrite(13, HIGH);

}

void update_address_bus() {

  // Address bus (Output)
  digitalWrite(A0P, cpu.A0);
  digitalWrite(A1P, cpu.A1);
  digitalWrite(A2P, cpu.A2);
  digitalWrite(A3P, cpu.A3);
  digitalWrite(A4P, cpu.A4);
  digitalWrite(A5P, cpu.A5);
  digitalWrite(A6P, cpu.A6);
  digitalWrite(A7P, cpu.A7);
  digitalWrite(A8P, cpu.A8);
  digitalWrite(A9P, cpu.A9);
  digitalWrite(A10P, cpu.A10);
  digitalWrite(A11P, cpu.A11);
  digitalWrite(A12P, cpu.A12);
  digitalWrite(A13P, cpu.A13);
  digitalWrite(A14P, cpu.A14);
  digitalWrite(A15P, cpu.A15);

}

void update_data_bus() {

  // Data Bus (Output)
  if (!dataBusMode) {
    digitalWrite(D0P, cpu.D0);
    digitalWrite(D1P, cpu.D1);
    digitalWrite(D2P, cpu.D2);
    digitalWrite(D3P, cpu.D3);
    digitalWrite(D4P, cpu.D4);
    digitalWrite(D5P, cpu.D5);
    digitalWrite(D6P, cpu.D6);
    digitalWrite(D7P, cpu.D7);
  }
  // Data Bus (Input)
  else {
    cpu.D0 = digitalRead(D0P);
    cpu.D1 = digitalRead(D1P);
    cpu.D2 = digitalRead(D2P);
    cpu.D3 = digitalRead(D3P);
    cpu.D4 = digitalRead(D4P);
    cpu.D5 = digitalRead(D5P);
    cpu.D6 = digitalRead(D6P);
    cpu.D7 = digitalRead(D7P);
  }

}
void update_pins() {

  update_general_outputs();
  update_general_inputs();
  update_address_bus();
  update_data_bus();

}

void loop() {

  update_pins();

  cpu.mainloop();

  if (cpu.PC) {
    Serial.print(cpu.PC, HEX);
  }

}
