/*
 * arduino-6502 (https://github.com/goncrust/arduino-6502)
 * 
 * Arduino main functions.
 *
 * Copyright (c) 2021 by goncrust
 * Released under the GPL v3.0
 * https://github.com/goncrust/arduino-6502/blob/main/LICENSE
 */


// RIGHT
#define RWB 7
// NC not used
#define BE 8
#define PHI2 9
#define SOB 10
#define PHI2O 11
#define RESB 12
// VSS not used

// LEFT
#define VPB 1
#define RDY 2
#define PHI1O 3 
#define IRQB 4
#define MLB 5
#define NMIB 6
#define SYNC 7
// VDD not used

// DATA BUS
#define D0 22
#define D1 24
#define D2 26
#define D3 28
#define D4 30
#define D5 32
#define D6 34
#define D7 36

// ADDRESS BUS
#define A0 23
#define A1 25
#define A2 27
#define A3 29
#define A4 31
#define A5 33
#define A6 35
#define A7 37
#define A8 39
#define A9 41
#define A10 43
#define A11 45
#define A12 47
#define A13 49
#define A14 51
#define A15 53

/* Set Data Bus pin mode 
 *  mode = 0 -> Output 
 *  mode = 1 -> Input
 */
void setDataBus(int mode) {

  if (mode) {
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
  } else {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
  }

}

void setup() {

  // Address Bus
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  pinMode(A11, OUTPUT);
  pinMode(A12, OUTPUT);
  pinMode(A13, OUTPUT);
  pinMode(A14, OUTPUT);
  pinMode(A15, OUTPUT);

  // Data Bus
  setDataBus(0);

  pinMode(BE, INPUT);
  pinMode(IRQB, INPUT);
  pinMode(MLB, OUTPUT);
  pinMode(NMIB, INPUT);
  pinMode(PHI2, INPUT);
  pinMode(PHI2O, OUTPUT);
  pinMode(PHI1O, OUTPUT);
  pinMode(RWB, OUTPUT);
  pinMode(RDY, INPUT);
  pinMode(RESB, INPUT);
  pinMode(SOB, INPUT);
  pinMode(SYNC, OUTPUT);
  pinMode(VPB, OUTPUT);

}

void loop() {
}
