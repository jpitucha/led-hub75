#define A 2
#define B 3
#define C 4
#define D 5
#define R1 A0
#define R2 A1
#define G1 A2
#define G2 A3
#define B1 A4
#define B2 A5
#define CLK 8
#define LATCH 9
#define OE 10

#define BLANK_DELAY_TIME_US 5000

byte vRamR[4][64] = {0};
byte vRamG[4][64] = {0};
byte vRamB[4][64] = {0};
byte currentRow = 0;

void nextRow() {
  if (currentRow == 0) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    currentRow = 1;
  } else if (currentRow == 1) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    currentRow = 2;
  } else if (currentRow == 2) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    currentRow = 3;
  } else if (currentRow == 3) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    currentRow = 4;
  } else if (currentRow == 4) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    currentRow = 5;
  } else if (currentRow == 5) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    currentRow = 6;
  } else if (currentRow == 6) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    currentRow = 7;
  } else if (currentRow == 7) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    currentRow = 8;
  } else if (currentRow == 8) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    currentRow = 9;
  } else if (currentRow == 9) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    currentRow = 10;
  } else if (currentRow == 10) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    currentRow = 11;
  } else if (currentRow == 11) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    currentRow = 12;
  } else if (currentRow == 12) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    currentRow = 13;
  } else if (currentRow == 13) {
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    currentRow = 14;
  } else if (currentRow == 14) {
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    currentRow = 15;
  } else if (currentRow = 15) {
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    currentRow = 0;
  }
}

void clkTick() {
  digitalWrite(CLK, HIGH);
  digitalWrite(CLK, LOW);
}

void latchTick() {
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}

void enableOutput() {
  digitalWrite(OE, LOW);
}

void disableOutput() {
  digitalWrite(OE, HIGH);
}

void shiftInData() {
  
}

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(OE, OUTPUT);

  for (int i = 0; i < 64; i++) {
    clkTick();
    latchTick();
  }
}

void loop() {
  enableOutput();
  shiftInData();
  latchTick();
  nextRow();
  disableOutput();
  delayMicroseconds(BLANK_DELAY_TIME_US);  
}
