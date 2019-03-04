/* ------------------------------------------------------------------------------

S030319 - HW ref: A191117  The Thing

NOTE: It is required the H170119 configuration file to be loaded into the FPGA.

Example using a custom multifunction controller for a 7-segments 4 digits led display, 3 leds and 4 buttons.
Drive a custom bidirectional interface (DATA_0-6) for a four digits (single segment drive) 7-segments display, three leds (LED1-3), and that can read the state of four buttons (USR3-7).

NOTE: Only DATA_0-3 are really bidirectional (see H170119 FPGA configuration file).

The 7-segment display multiplexing is done internally in the FPGA (see H170119 FPGA configuration file).

--------------------------------------------------------------------------------- */


// ------------------------------------------------------------------------------
//
// Hardware definitions for A191117
//
// ------------------------------------------------------------------------------

#define LED_PB1 PB1       // HIGH = ON
#define USR1    PC13      // USR1 button (LOW when pressed)
#define USR2    PC14      // USR2 button (LOW when pressed)
#define USR3    PC15      // USR3 button (LOW when pressed)
#define BUT     PB8       // BUT button (HIGH when pressed)

// ------------------------------------------------------------------------------
//
// Hardware definitions for the H170119 FPGA configuration file
//
// ------------------------------------------------------------------------------

#define DATA_0  PA4        // Data bus line 0
#define DATA_1  PA5        // Data bus line 1
#define DATA_2  PA6        // Data bus line 2
#define DATA_3  PA7        // Data bus line 3
#define DATA_4  PB10       // Data bus line 4
#define DATA_5  PB11       // Data bus line 5
#define DATA_6  PB12       // Data bus line 6
#define SEL_0   PB13       // Register address line 0
#define SEL_1   PB14       // Register address line 1
#define SEL_2   PB15       // Register address line 2
#define WR_EN   PA8        // Register write enable
#define RD_EN   PB6        // Register read enable
#define FPGA_EN PB7        // FPGA runnig status line (0 = running)

// ------------------------------------------------------------------------------
//
//  Global constants
//
// ------------------------------------------------------------------------------

const byte Dig0 = B11111100;  // Segments binary code: B< A, B, C, D, E, F, G, NOT USED ( = 0) >
const byte Dig1 = B01100000;
const byte Dig2 = B11011010;
const byte Dig3 = B11110010;
const byte Dig4 = B01100110;
const byte Dig5 = B10110110;
const byte Dig6 = B10111110;
const byte Dig7 = B11100000;
const byte Dig8 = B11111110;
const byte Dig9 = B11110110;
const byte A = B11101110;
const byte B = B00111110;
const byte C = B10011100;
const byte D = B01111010;
const byte E = B10011110;
const byte F = B10001110;
const byte H = B01101110;
const byte I = B00001100;
const byte L = B00011100;
const byte M = B11101100;
const byte N = B00101010;
const byte O = B11111100;
const byte P = B11001110;
const byte R = B00001010;
const byte S = B10110110;
const byte T = B10001100;
const byte U = B01111100;
const byte Z = B11011010;
const byte K = B00001110;
const byte Y = B01110110;
const byte Blank = B00000000;
const byte Bar = B00000010;
const byte demoBanner[] = {Blank, Blank, Blank, T, H, E, Blank, T, H, I, N, Dig6 ,Blank, F, P, Dig6, A, Blank, Blank, Blank, 
                          M, U, L, T, I, F, U, N, C, T, I, O, N, Blank, C, U, S, T, O, M, Blank, I, Bar, F, Blank, D, E, M, O, Blank, 
                          H, Dig1, Dig7, Dig0, Dig1, Dig1, Dig9, Blank, Blank, Blank};
const int  delayTime = 400;

// ------------------------------------------------------------------------------
//
//  Global variables
//
// ------------------------------------------------------------------------------

int           demoLeng, i = 0;
byte          leds = B00001000, j, buttonCode, buttonName[4];
unsigned long timeStamp;

// ------------------------------------------------------------------------------

void setup() 
{
  // Set the MCU side for the the H170119 FPGA configuration file
  // Note: the pull-up resistors are already set inside the FPGA
  pinMode(DATA_4, OUTPUT);
  pinMode(DATA_5, OUTPUT);
  pinMode(DATA_6, OUTPUT);
  //pinMode(DATA_7, OUTPUT);
  pinMode(SEL_0, OUTPUT);
  pinMode(SEL_1, OUTPUT);
  pinMode(SEL_2, OUTPUT);
  pinMode(WR_EN, OUTPUT);
  digitalWrite(WR_EN, HIGH);
  pinMode(RD_EN, OUTPUT);
  digitalWrite(RD_EN, HIGH);
 
  // Set the MCU buttons and led
  pinMode(LED_PB1, OUTPUT);
  pinMode(USR1, INPUT_PULLUP);
  pinMode(USR2, INPUT_PULLUP);
  pinMode(USR3, INPUT_PULLUP);
  pinMode(BUT, INPUT);

  // Other settings
  digitalWrite(LED_PB1, LOW);       // Led OFF
  pinMode(FPGA_EN, INPUT_PULLUP);   // FPGA_EN as input

  // Calculate size (bytes) of the demo string
  demoLeng = sizeof(demoBanner);
}

void loop() 
{
  if (!buttonCode)
  {
    // Display data on the 7-segments display
    writeReg(demoBanner[i], 3);
    writeReg(demoBanner[(i+1) % demoLeng], 2);
    writeReg(demoBanner[(i+2) % demoLeng], 1);
    writeReg(demoBanner[(i+3) % demoLeng], 0);
    i = (i + 1) % demoLeng;

    // Running light on leds LED1-3
    writeReg(leds, 4);
    leds = leds >> 1;
    if (leds <= 1) leds = B00001000;
  }
  else
  // Display pressed button name
  {
    buttonName[0] = U;
    buttonName[1] = S;
    buttonName[2] = R;
    switch (buttonCode)
    {
      case 1:
        leds = 9;
        buttonName[3] = Dig1;        
      break;
      case 2:
        leds = 9;
        buttonName[3] = Dig2;        
      break;
      case 3:
        leds = 9;
        buttonName[3] = Dig3;        
      break;
      case 4:
        leds = B00000010;
        buttonName[3] = Dig4;        
      break;
      case 5:
        leds = B00000100;
        buttonName[3] = Dig5;        
      break;
      case 6:
        leds = B00001000;
        buttonName[3] = Dig6;        
      break;
      case 7:
        leds = B00000000;
        buttonName[3] = Dig7;        
      break;
      case 8:
        leds = 9;
        buttonName[0] = B;
        buttonName[1] = U;
        buttonName[2] = T;
        buttonName[3] = Blank;        
      break;
    }
    
    for (j = 0; j < 4; j++)
    // Blink the name of the pressed button
    {
      writeReg(buttonName[0], 3);
      writeReg(buttonName[1], 2);
      writeReg(buttonName[2], 1);
      writeReg(buttonName[3], 0);
      if (leds < 9) writeReg(leds, 4);
      else digitalWrite(LED_PB1, HIGH);
      delay(100);
      writeReg(Blank, 3);
      writeReg(Blank, 2);
      writeReg(Blank, 1);
      writeReg(Blank, 0);
      writeReg(0, 4);
      digitalWrite(LED_PB1, LOW);
      delay(100);
    }
    buttonCode = 0;
    leds = 0;
  }

  do
  // Check if any button is pressed during delay
  {
    if (!buttonCode) buttonCode = checkButton();
  }
  while (millis() < (timeStamp + delayTime));
  timeStamp = millis();
}

// ------------------------------------------------------------------------------

void writeReg(byte dataByte, byte regAddress)
// Write a data byte into one of the custom interface registers. There are five writable registers: four for the 7-segments display digits and one for the four LED1-3 leds.
// NOTE: only DATA_0-3 are really bidirectional (see H170119 FPGA configuration file).
// Usage:
//  dataByte is the data byte to write in the selected register;
//  regAddress is the three bit address of the custom interface register to write (valid addresses are from 0x0 to 0x4).
{
  // Set DATA_0-3 as outputs
  pinMode(DATA_0, OUTPUT);
  pinMode(DATA_1, OUTPUT);
  pinMode(DATA_2, OUTPUT);
  pinMode(DATA_3, OUTPUT);

  // Write DATA lines
  digitalWrite(DATA_6, HIGH && (dataByte & B10000000));
  digitalWrite(DATA_5, HIGH && (dataByte & B01000000));
  digitalWrite(DATA_4, HIGH && (dataByte & B00100000));
  digitalWrite(DATA_3, HIGH && (dataByte & B00010000));
  digitalWrite(DATA_2, HIGH && (dataByte & B00001000));
  digitalWrite(DATA_1, HIGH && (dataByte & B00000100));
  digitalWrite(DATA_0, HIGH && (dataByte & B00000010));

  // Write SEL lines (display register address)
  digitalWrite(SEL_2, HIGH && (regAddress & B00000100));
  digitalWrite(SEL_1, HIGH && (regAddress & B00000010));
  digitalWrite(SEL_0, HIGH && (regAddress & B00000001));

  // Write into the selected register using a pulse on the WR_EN line
  digitalWrite(WR_EN, LOW);
  digitalWrite(WR_EN, HIGH);
}

// ------------------------------------------------------------------------------

byte readReg()
// Read the status of the USR4-7 buttons in the low nibble from the custom interface. The high nibble is filled with zeroes. 
// No address is required on the SEL_0-2 lines.
// NOTE: only DATA_0-3 are really bidirectional (see H170119 FPGA configuration file).
{
  byte  tempByte = 0;
  
  // Set DATA_0-3 as inputs
  pinMode(DATA_0, INPUT);
  pinMode(DATA_1, INPUT);
  pinMode(DATA_2, INPUT);
  pinMode(DATA_3, INPUT);

  // Read the USR4-7 buttons state nibble enabling the RD_EN line if the FPGA is running (FPGA_EN = 0)
  if (digitalRead(FPGA_EN) == 0)
  {
    digitalWrite(RD_EN, LOW);
    tempByte = tempByte | digitalRead(DATA_0);
    tempByte = tempByte | (digitalRead(DATA_1) << 1);
    tempByte = tempByte | (digitalRead(DATA_2) << 2);
    tempByte = tempByte | (digitalRead(DATA_3) << 3);
    digitalWrite(RD_EN, HIGH);
  }

  // Read again the FPGA_EN input status line and decide if the key is valid
  if (digitalRead(FPGA_EN) == 1) return 0;  // Not valid. No key really pressed
  else return tempByte;                     // Yes, it is valid
}

// ------------------------------------------------------------------------------

byte checkButton()
// Check if any USR1-7 or BUT button is pressed. Only one button at time is read.
// Returned value: 1 -> USR1, 2 -> USR2, 3 -> USR3, 4 -> USR4, 5 -> USR5, 6 -> USR6, 7 -> USR7, 8 -> BUT.
{
  byte tempByte = 0;
  
  if (!digitalRead(USR1)) tempByte = 1;
  if (!digitalRead(USR2)) tempByte = 2;
  if (!digitalRead(USR3)) tempByte = 3;
  if (digitalRead(BUT)) tempByte = 8;
  if ((readReg() & B00000001)) tempByte = 4;
  if ((readReg() & B00000010)) tempByte = 5;
  if ((readReg() & B00000100)) tempByte = 6;
  if ((readReg() & B00001000)) tempByte = 7;
  return tempByte;
}

