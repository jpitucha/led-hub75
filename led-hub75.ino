/**
 * P4-64x32
 * 
 * CONNECTION SCHEMA
 * A - 2
 * B - 3
 * C - 4
 * D - 5
 * CLK - 8
 * LATCH - 9
 * OE - 10
 * R1 - A0
 * R2 - A1
 * G1 - A2
 * G2 - A3
 * B1 - A4
 * B2 - A5
 * 
 * PORT D reserved only for ABCD
**/

#define HOLD_DELAY_TIME_US 199
#define BLANK_DELAY_TIME_US 1

byte vRamR[4][64] = {0};
byte vRamG[4][64] = {0};
byte vRamB[4][64] = {0};
byte currentRow = 0;

void nextRow() {
  if (currentRow == 0) {
    PORTD = 0b00111100;
    currentRow = 1;
  } else if (currentRow == 1) {
    PORTD = 0b00111000;
    currentRow = 2;
  } else if (currentRow == 2) {
    PORTD = 0b00110100;
    currentRow = 3;
  } else if (currentRow == 3) {
    PORTD = 0b00110000;
    currentRow = 4;
  } else if (currentRow == 4) {
    PORTD = 0b00101100;
    currentRow = 5;
  } else if (currentRow == 5) {
    PORTD = 0b00101000;
    currentRow = 6;
  } else if (currentRow == 6) {
    PORTD = 0b00100100;
    currentRow = 7;
  } else if (currentRow == 7) {
    PORTD = 0b00100000;
    currentRow = 8;
  } else if (currentRow == 8) {
    PORTD = 0b00011100;
    currentRow = 9;
  } else if (currentRow == 9) {
    PORTD = 0b00011000;
    currentRow = 10;
  } else if (currentRow == 10) {
    PORTD = 0b00010100;
    currentRow = 11;
  } else if (currentRow == 11) {
    PORTD = 0b00010000;
    currentRow = 12;
  } else if (currentRow == 12) {
    PORTD = 0b00001100;
    currentRow = 13;
  } else if (currentRow == 13) {
    PORTD = 0b00001000;
    currentRow = 14;
  } else if (currentRow == 14) {
    PORTD = 0b00000100;
    currentRow = 15;
  } else if (currentRow = 15) {
    PORTD = 0b00000000;
    currentRow = 0;
  }
}

void clkTick() { PORTB |= 1; PORTB &= ~1; }
void latchTick() { PORTB |= (1 << 1); PORTB &= ~(1 << 1); }
void enableOutput() { PORTB &= ~(1 << 2); }
void disableOutput() { PORTB |= (1 << 2); }
void shiftInData() {
  if (currentRow < 8) {
    for (int i = 0; i < 64; i++) {
      if (bitRead(vRamR[0][63 - i], currentRow % 8)) PORTC |= 0b00000010; else PORTC &= ~0b00000010;
      if (bitRead(vRamG[0][63 - i], currentRow % 8)) PORTC |= 0b00001000; else PORTC &= ~0b00001000;
      if (bitRead(vRamB[0][63 - i], currentRow % 8)) PORTC |= 0b00100000; else PORTC &= ~0b00100000;

      if (bitRead(vRamG[2][63 - i], currentRow % 8)) PORTC |= 0b00000001; else PORTC &= ~0b00000001;
      if (bitRead(vRamG[2][63 - i], currentRow % 8)) PORTC |= 0b00000100; else PORTC &= ~0b00000100;
      if (bitRead(vRamB[2][63 - i], currentRow % 8)) PORTC |= 0b00010000; else PORTC &= ~0b00010000;

      clkTick();
    }
  } else {
    for (int i = 0; i < 64; i++) {
      if (bitRead(vRamR[1][63 - i], currentRow % 8)) PORTC |= 0b00000010; else PORTC &= ~0b00000010;
      if (bitRead(vRamG[1][63 - i], currentRow % 8)) PORTC |= 0b00001000; else PORTC &= ~0b00001000;
      if (bitRead(vRamB[1][63 - i], currentRow % 8)) PORTC |= 0b00100000; else PORTC &= ~0b00100000;

      if (bitRead(vRamG[3][63 - i], currentRow % 8)) PORTC |= 0b00000001; else PORTC &= ~0b00000001;
      if (bitRead(vRamG[3][63 - i], currentRow % 8)) PORTC |= 0b00000100; else PORTC &= ~0b00000100;
      if (bitRead(vRamB[3][63 - i], currentRow % 8)) PORTC |= 0b00010000; else PORTC &= ~0b00010000;

      clkTick();
    }
  }
}

void setup() {
  DDRB |= 0b00000111; //Clk's
  DDRC |= 0b00111111; //Data
  DDRD |= 0b00111100; //ABCD

  vRamG[0][0] = 126;
  vRamG[0][1] = 129;
  vRamG[0][2] = 189;
  vRamG[0][3] = 165;
  vRamG[0][4] = 165;
  vRamG[0][5] = 189;
  vRamG[0][6] = 161;
  vRamG[0][7] = 30;
  
  vRamG[0][9] = 126;
  vRamG[0][10] = 129;
  vRamG[0][11] = 129;
  vRamG[0][12] = 126;
  
  vRamG[0][14] = 255;
  vRamG[0][15] = 137;
  vRamG[0][16] = 137; 
  vRamG[0][17] = 118;
  
  vRamG[0][19] = 143;
  vRamG[0][20] = 137;
  vRamG[0][21] = 137;
  vRamG[0][22] = 249;
  
  vRamG[0][24] = 255;
  vRamG[0][25] = 129;
  vRamG[0][26] = 129;
  vRamG[0][27] = 129;
  
  vRamG[0][29] = 255;
  vRamG[0][30] = 137;
  vRamG[0][31] = 137;
  vRamG[0][32] = 137;
  
  vRamG[0][34] = 255;
  vRamG[0][35] = 2;
  vRamG[0][36] = 60;
  vRamG[0][37] = 64;
  vRamG[0][38] = 255;
  
  vRamG[0][40] = 255;
  
  vRamG[0][42] = 126;
  vRamG[0][43] = 129;
  vRamG[0][44] = 129;
  vRamG[0][45] = 129;

  vRamG[0][47] = 193;
  vRamG[0][48] = 161;
  vRamG[0][49] = 153;
  vRamG[0][50] = 133;
  vRamG[0][51] = 131;
  
  vRamG[0][53] = 255;
  vRamG[0][54] = 2;
  vRamG[0][55] = 60;
  vRamG[0][56] = 64;
  vRamG[0][57] = 255;

  vRamG[0][59] = 1;
  vRamG[0][60] = 2;
  vRamG[0][61] = 252;
  vRamG[0][62] = 2;
  vRamG[0][63] = 1;
  
  //pre-clearing the display
  disableOutput();
  for (int i = 0; i < 64; i++) clkTick();
  latchTick();
  enableOutput();
}

void loop() {
  shiftInData();
  latchTick();
  nextRow();
  enableOutput();
  delayMicroseconds(HOLD_DELAY_TIME_US);
  disableOutput();
  delayMicroseconds(BLANK_DELAY_TIME_US);  
}
