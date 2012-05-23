#include <TimerOne.h>

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int  _charoffset[82]; 
byte _repcharoff;

int  _charspacing; 
char *_outputstring;
char *_curchr;
boolean  _hastext; 
int  _colct;
int _fontidx;
int j = 0;

// Font Data
PROGMEM prog_uchar _font[] = {
  // -------- Space
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  // -------- A
  0b01111110,
  0b10010000,
  0b10010000,
  0b01111110,
  // -------- B
  0b01101100,
  0b10010010,
  0b10010010,
  0b11111110,
  // -------- C
  0b10000010,
  0b10000010,
  0b01111100,
  // -------- D
  0b00111000,
  0b01000100,
  0b10000010,
  0b11111110,    
  // -------- E
  0b10000010,    
  0b10010010,    
  0b11111110,
  // -------- F
  0b10000000,        
  0b10010000,        
  0b11111110,
  // -------- G
  0b01011100,      
  0b10010010,
  0b10000010,
  0b01111100,
  // -------- H
  0b11111110,
  0b00010000,
  0b00010000,
  0b11111110,     
  // -------- I
  0b10000010,    
  0b11111110,    
  0b10000010,    
  // -------- J
  0b11111100,     
  0b00000010,
  0b00001100,
  // -------- K
  0b10000110,     
  0b01001000,     
  0b00110000,
  0b11111110,
  // -------- L
  0b00000010,      
  0b00000010,      
  0b11111110,
  // -------- M
  0b11111110,
  0b01100000,
  0b00111100,      
  0b01100000,      
  0b11111110, 
  // -------- N
  0b11111110,
  0b00011000,
  0b01100000,      
  0b11111110,     
  // -------- O
  0b01111100,
  0b10000010,
  0b10000010,
  0b01111100,      
  // -------- P
  0b01100000,    
  0b10010000,
  0b10010000,
  0b11111110,
  // -------- Q
  0b01111010,
  0b10000100,
  0b10001010,
  0b01111100,     
  // -------- R
  0b01100110,      
  0b10011000,
  0b10010000,
  0b11111110,
  // -------- S
  0b10001100,
  0b10010010,
  0b01100010,    
  // -------- T
  0b10000000,      
  0b11111110,
  0b10000000,      
  // -------- U
  0b11111100,
  0b00000010,
  0b00000010,
  0b11111100,       
  // -------- V
  0b11000000,
  0b00111000,
  0b00000110,
  0b00111000,
  0b11000000,       
  // -------- W
  0b11111110,
  0b00001100,
  0b00111000,      
  0b00001100,      
  0b11111110,     
  // -------- X
  0b11000110,
  0b00111000,
  0b00111000,     
  0b11000110,
  // -------- Y
  0b11100000,
  0b00011110,
  0b11100000,    
  // -------- Z
  0b11000010,
  0b10110010,
  0b10001110,      
  // -------- Unknown character
  0b00111000,      
  0b00111000,
  0b00111000,
  // -------- 0
  0b01111100,
  0b10100010,
  0b10010010,
  0b01111100,      
  // -------- 1
  0b11111110,
  0b01000000,
  // -------- 2
  0b01100010,
  0b10010010,
  0b10001110,      
  // -------- 3
  0b01101100,
  0b10010010,
  0b10000010,      
  // -------- 4
  0b11111110,
  0b00010000,
  0b11110000,      
  // -------- 5
  0b10001100,
  0b10010010,
  0b11110010,      
  // -------- 6
  0b01001100,
  0b10010010,
  0b10010010,
  0b01111100,      
  // -------- 7
  0b11100000,
  0b10011110,
  0b10000000,      
  // -------- 8
  0b01101100,
  0b10010010,
  0b10010010,
  0b01101100,      
  // -------- 9
  0b01111100,
  0b10010010,
  0b10010010,
  0b01100100,      
  // -------- :
  0b00100100,
  // -------- ;
  0b00100110,
  0b00000001,
  // -------- !
  0b01100000,
  0b11111010,
  0b01100000,
  // -------- Heart
  0b01111000,
  0b11111100,
  0b11111110,
  0b01111111,
  0b11111110,
  0b11111100,
  0b01111000,
  // -------- <
  0b01000100,
  0b00101000,
  0b00010000,
  // -------- =
  0b00101000,
  0b00101000,
  0b00101000,
  0b00101000,
  // -------- >
  0b00010000,
  0b00101000,
  0b01000100,
  // -------- ?
  0b01100000,
  0b10011010,
  0b10000000,
  // -------- @
  0b01111100,
  0b10000010,
  0b10111010,
  0b10100010,
  0b01011100,
  // -------- (
  0b10000010,
  0b01111100,
  // -------- )
  0b01111100,
  0b10000010,
  // -------- *
  0b00101000,
  0b00010000,
  0b00101000,
  // -------- +
  0b00010000,
  0b00010000,
  0b01111100,
  0b00010000,
  0b00010000,
  // -------- ,
  0b00000110,
  0b00000001,   
  // -------- -
  0b00010000,
  0b00010000,
  0b00010000,
  0b00010000,
  // -------- .
  0b00000010,
  // -------- /
  0b11000000,
  0b00111000,
  0b00000110,
  // -------- a
  0b00111110,
  0b00100010,
  0b00100010,
  0b00011100,
  // -------- b
  0b00011100,
  0b00100010,
  0b00100010,
  0b11111110,
  // -------- c
  0b00100010,
  0b00100010,
  0b00011100,
  // -------- d
  0b11111110,
  0b00100010,
  0b00100010,
  0b00011100,
  // -------- e
  0b00011000,
  0b00101010,
  0b00101010,
  0b00011100,
  // -------- f
  0b10010000,
  0b01111110,
  0b00010000,
  // -------- g
  0b00111110,
  0b00100101,
  0b00100101,
  0b00011000,
  // -------- h
  0b00011110,
  0b00100000,
  0b00100000,
  0b11111110,
  // -------- i
  0b00000010,
  0b01011110,
  0b00010010,
  // -------- j
  0b01011110,
  0b00000001,
  0b00000001,
  // -------- k
  0b00100010,
  0b00010100,
  0b00001000,
  0b11111110,
  // -------- l
  0b00000010,
  0b11111100,
  // -------- m
  0b00011110,
  0b00100000,
  0b00111110,
  0b00100000,
  0b00111110,
  // -------- n
  0b00011110,
  0b00100000,
  0b00100000,
  0b00111110,
  // -------- o
  0b00011100,
  0b00100010,
  0b00100010,
  0b00011100,
  // -------- p
  0b00011100,
  0b00100010,
  0b00100010,
  0b00111111,
  // -------- q
  0b00111111,
  0b00100010,
  0b00100010,
  0b00011100,
  // -------- r
  0b00010000,
  0b00100000,
  0b00111110,
  // -------- s
  0b00100100,
  0b00101010,
  0b00101010,
  0b00010010,
  // -------- t
  0b00100010,
  0b11111100,
  0b00100000,
  // -------- u
  0b00111110,
  0b00000010,
  0b00000010,
  0b00111100,
  // -------- v
  0b00111000,
  0b00000110,
  0b00111000,
  // -------- w
  0b00111110,
  0b00000010,
  0b00011110,
  0b00000010,
  0b00111100,
  // -------- x
  0b00110110,
  0b00001000,
  0b00110110,
  // -------- y
  0b00111110,
  0b00000101,
  0b00000101,
  0b00111001,
  // -------- z
  0b00110010,
  0b00101010,
  0b00100110,
  0b00100010, 
  0b11000001
};

// Char width table
PROGMEM prog_uchar _charwidth[] = {
  4,4,4,3,4,3,3,4,4,3,3,4,3,5,4,4,4,4,4,3,3,4,5,5,4,3,3,
  3,4,2,3,3,3,3,4,3,4,4,1,2,3,7,3,4,3,3,5,2,2,3,5,2,4,1,3,
  4,4,3,4,4,3,4,4,3,3,4,2,5,4,4,4,4,3,4,3,4,3,5,3,4,4,0 };

// ASCII Codes of the implemented characters                                    
PROGMEM prog_uchar _charcodes[] = {
  32,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
  81,82,83,84,85,86,87,88,89,90,255,48,49,50,51,52,53,
  54,55,56,57,58,59,33,3,60,61,62,63,64,40,41,42,43,44,
  45,46,47,97,98,99,100,101,102,103,104,105,106,107,108,
  109,110,111,112,113,114,115,116,117,118,119,120,121,
  122,0};

byte buffer[8];



void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  calculateCharOffsets();
  clear();
  Timer1.initialize(10000);         // initialize timer1, and set a 1/2 second period
  // Timer1.attachInterrupt(update); 
}

void clear() {
  for (int i = 0; i< 8; i++) {
    buffer[i] = 0;
  }
}

void fill() {
  for (int i = 0; i< 8; i++) {
    buffer[i] = 255;
  }
}

void setLed(byte x, byte y, byte value)
{
  if (value) {
    buffer[x] |= value << (7-y);
  }
  else {
    buffer[x] &= ~(1 << (7-y)); 
  }
}

void update()
{
  for (byte i=0; i<8; i++) {
    writeColumn(i, buffer[i]);
  }
}

void shiftLeft() {
  for (int i = 0 ; i < 8; i++) {
    buffer[i] = buffer[i] << 1;
  }
}

void shiftRight() {
  for (int i = 0 ; i < 8; i++) {
    buffer[i] = buffer[i] >> 1;
  }
}

void shiftUp() {
  for (int i = 1 ; i < 8; i++) {
    buffer[i-1] = buffer[i];
  }
  buffer[7] = 0;
}

void shiftDown() {
  for (int i = 7 ; i >0 ; i--) {
    buffer[i] = buffer[i-1];
  }
  buffer[0] = 0;
}

void writeColumn( byte column,  byte data)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST,data);   
  shiftOut(dataPin, clockPin, LSBFIRST, (1 << (column)));
  digitalWrite(latchPin, HIGH);
}

byte drawChar (int x, int y, char thechar)
{
  y+=7;
  byte charnum, colct, count=0, colbits;
  int fontidx;
  charnum = getInternalCharCode(thechar);

  // get the location of the first column of the font
  fontidx = _charoffset[charnum]-1;

  // get the width of the font
  colct = pgm_read_byte_near(_charwidth + charnum);
  for (byte i=colct; i>0; i--) {
    colbits = pgm_read_byte_near(_font + fontidx + i);
    for (byte j=0; j<=7; j++) {
      if ((colbits >>j) & 1) {
        setLed(x, y-j, 1);
      }
    }
    x++;
  }
  return colct+1;
}

// ------------------------------------------------------------------------------------
// calculates Character offsets from font width table in EEPROM
void calculateCharOffsets()
{
  int off =0;
  int idx=0;
  int w=0;
  int i=0;

  do {
    _charoffset[i]=off;
    w = pgm_read_byte_near(_charwidth+i);
    off += w;
    i++;
  } while (w != 0);
}

// ------------------------------------------------------------------------------------
// gets the character number of the built-in-font from the ASCII table
// returns number of the replacement character for unknown characters
byte getInternalCharCode(byte thechar)
{
    int i=0;
    int charnum;
    do {
      charnum = pgm_read_byte_near(_charcodes + i);
      if (charnum == thechar) break;
      i++;
    } while (charnum != 0 );
    if (charnum == 0) i = _repcharoff;
    return i;
}


void setScrollText(char *string, int charspacing)
{
  _charspacing = charspacing;
  _outputstring = string;
  _curchr = string;
  _hastext = true;
  _colct =-1;
}

boolean textScroll()
{
  boolean lastchar = false;
  byte colbits = 0;
  if (_colct == (0-_charspacing-1)) {
    lastchar = nextCharacter();
  }
  if (_colct>=0) {
    colbits = pgm_read_byte_near(_font + _fontidx + _colct);
  }
  shiftUp();
  buffer[7] = colbits;
  update();
  _colct--;
  return lastchar;
}

boolean nextCharacter()
{
  boolean lastchar = false;
  if (_hastext) {
    char thechar = *_curchr;
    boolean found = false;
    byte charnum = 0;
    byte i;
    // if the string ends, start from the beginning
    if (thechar == 0) {
      lastchar = true;
      _curchr = _outputstring;
      thechar = *_curchr;
    }

    charnum = getInternalCharCode(thechar);

    // get the offset of the first column of the character
    _fontidx = _charoffset[charnum];

    // get the width of the font
    _colct = pgm_read_byte_near(_charwidth + charnum) -1;
  }
  else {
    _fontidx= _charoffset[_repcharoff];
    _colct = pgm_read_byte_near(_charwidth + _repcharoff);
  }
  *_curchr++;
  return lastchar;
}

void loop() {
  
  char *text = "   Text hier eingeben      ";
  setScrollText(text, 2);
  
  while (!textScroll()) {
    for (int i = 0; i < 10; i++) update();
   
  }
  
}






