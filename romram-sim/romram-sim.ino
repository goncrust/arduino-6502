
// Data Bus
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// Address Bus
#define AD0 13
#define AD1 12
#define AD2 11
#define AD3 10
#define AD4 9
#define AD5 8
#define AD6 A0
#define AD7 A1
#define AD8 A2
#define AD9 A3
#define AD10 A4

// RWB
#define RWB A5

typedef unsigned char BYTE;
typedef short WORD;

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

// Actual memory
BYTE mem[0x6FF + 1];

void setup() {  

  // Decisions:
  // Zero page (256 bytes): ($0000-$00FF)
  // Stack (256 bytes): ($0100-$01FF)
  // RAM: ($0200-$03FF)
  // ROM: ($0400-$06F9)
  // Addresses of the non-maskable interrupt handler: ($06FA/B)
  // Power/reset location: ($06FC/D)
  // BRK/interrupt request handler: ($07FE/F)

  // Memory
  mem[0x06FC] = 0x00;
  mem[0x06FD] = 0x04; 
  mem[0x0400] = 0x12;

  // Data Bus
  setDataBus(0);

  // Address Bus 
  pinMode(AD0, INPUT);
  pinMode(AD1, INPUT);
  pinMode(AD2, INPUT);
  pinMode(AD3, INPUT);
  pinMode(AD4, INPUT);
  pinMode(AD5, INPUT);
  pinMode(AD6, INPUT);
  pinMode(AD7, INPUT);
  pinMode(AD8, INPUT);
  pinMode(AD9, INPUT);
  pinMode(AD10, INPUT);
  
  // RW Bus
  pinMode(RWB, INPUT);

  //Serial.begin(9600);
}

WORD readAB () {

  WORD ab = 0;
  
  if (digitalRead(AD0)) {
    Serial.print("1");
    ab |= 0b0000000000000001;
  } else Serial.print("0");
  
  if (digitalRead(AD1)) {
    Serial.print("1");
    ab |= 0b0000000000000010;
  } else Serial.print("0");

  if (digitalRead(AD2)) {
    Serial.print("1");
    ab |= 0b0000000000000100;
  } else Serial.print("0");

  if (digitalRead(AD3)) {
    Serial.print("1");
    ab |= 0b0000000000001000;
  } else Serial.print("0");

  if (digitalRead(AD4)) {
    Serial.print("1");
    ab |= 0b0000000000010000;
  } else Serial.print("0");

  if (digitalRead(AD5)) {
    Serial.print("1");
    ab |= 0b0000000000100000;
  } else Serial.print("0");

  if (digitalRead(AD6)) {
    Serial.print("1");
    ab |= 0b0000000001000000;
  } else Serial.print("0");

  if (digitalRead(AD7)) {
    Serial.print("1");
    ab |= 0b0000000010000000;
  } else Serial.print("0");

  if (digitalRead(AD8)) {
    Serial.print("1");
    ab |= 0b0000000100000000;
  } else Serial.print("0");

  if (digitalRead(AD9)) {
    Serial.print("1");
    ab |= 0b0000001000000000;
  } else Serial.print("0");

  if (digitalRead(AD10)) {
    Serial.print("1");
    ab |= 0b0000010000000000;
  } else Serial.print("0");

  Serial.println("");
  Serial.println("");

  Serial.print("ab: ");
  Serial.print(ab, HEX);
  
  Serial.println("");
  Serial.println("");

  return ab;
}

void outputD(BYTE data) {

  setDataBus(0);
  
  for (int i = 0; i < 8; i++) {

    if ((data >> i) & 0b00000001) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }

  }

}

BYTE readD() {

  setDataBus(1);

  BYTE data = 0;

  if (digitalRead(D0)) data |= 0b00000001;
  if (digitalRead(D1)) data |= 0b00000010;
  if (digitalRead(D2)) data |= 0b00000100;
  if (digitalRead(D3)) data |= 0b00001000;
  if (digitalRead(D4)) data |= 0b00010000;
  if (digitalRead(D5)) data |= 0b00100000;
  if (digitalRead(D6)) data |= 0b01000000;
  if (digitalRead(D7)) data |= 0b10000000;

  return data;
}


void loop() {
    
  // Read address bus
  WORD address = readAB();

  // Overflow
  if (address > 0x6FF && !(address >= 0x7FA && address <= 0x7FF)) {
    outputD(0);
    return;
  }

  // Read RWB
  if (digitalRead(RWB)) {

    // Return data
    if (address == 0x7FA) outputD(mem[0x6FA]);
    else if (address == 0x7FB) outputD(mem[0x6FB]);
    else if (address == 0x7FC) outputD(mem[0x6FC]);
    else if (address == 0x7FD) outputD(mem[0x6FD]);
    else if (address == 0x7FE) outputD(mem[0x6FE]);
    else if (address == 0x7FF) outputD(mem[0x6FF]);
    else outputD(mem[address]);

  } else {
    // Make sure address is in RAM space
    if (address < 0x0400) mem[address] = readD();
  }


}
