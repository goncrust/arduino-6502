
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

void setup() {

  //Data Bus
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
  
  for (int i = 0; i < 8; i++) {

    Serial.println("OUTPUT");
    if ((data >> i) & 0b00000001) {
      Serial.print("1");
      digitalWrite(i, HIGH);
    } else {
      Serial.print("0");
      digitalWrite(i, LOW);
    }
    Serial.println("");

  }

}

void loop() {

  // READ
  if (digitalRead(RWB)) {
    WORD address = readAB();

    Serial.print("AQUIIII:");
    Serial.print(address, HEX);

    setDataBus(0);
    if (address == 0x7FC) {
        outputD(0x42);
    } else if (address == 0x7FD) {
        outputD(0x40);
    }
  }


}
