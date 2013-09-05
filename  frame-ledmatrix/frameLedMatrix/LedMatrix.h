
/*

LED Panel Layout in RAM
                            32 pixels (4 bytes)
        top left  ----------------------------------------
                  |                                      |
         Screen 1 |        512 pixels (64 bytes)         | 16 pixels
                  |                                      |
                  ---------------------------------------- bottom right

 ---

 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------*/

#ifndef LedMatrix_h
#define LedMatrix_h


//Arduino toolchain header, version dependent
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


//SPI library must be included for the SPI scanning/connection method to the DMD
#include "pins_arduino.h"
#include <avr/pgmspace.h>
#include <SPI.h>


//#include "Arduino.h"
#define SIZE 32
//#####################################################################################################################
// ######################################################################################################################
#warning CHANGE THESE TO SEMI-ADJUSTABLE PIN DEFS!
//Arduino pins used for the display connection
#define PIN_LedMatrix_nOE       9    // D9 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_LedMatrix_A         6    // D6
#define PIN_LedMatrix_B         7    // D7
#define PIN_LedMatrix_CLK       13   // D13_SCK  is SPI Clock if SPI is used
#define PIN_LedMatrix_SCLK      10    // D8
#define PIN_LedMatrix_R_DATA    11   // D11_MOSI is SPI Master Out if SPI is used
//Define this chip select pin that the Ethernet W5100 IC or other SPI device uses
//if it is in use during a DMD scan request then scanDisplayBySPI() will exit without conflict! (and skip that scan)
#define PIN_OTHER_SPI_nCS 8
// ######################################################################################################################
// ######################################################################################################################

//DMD I/O pin macros
#define LIGHT_DMD_ROW_01_05_09_13()       { digitalWrite( PIN_DMD_B,  LOW ); digitalWrite( PIN_DMD_A,  LOW ); }
#define LIGHT_DMD_ROW_02_06_10_14()       { digitalWrite( PIN_DMD_B,  LOW ); digitalWrite( PIN_DMD_A, HIGH ); }
#define LIGHT_DMD_ROW_03_07_11_15()       { digitalWrite( PIN_DMD_B, HIGH ); digitalWrite( PIN_DMD_A,  LOW ); }
#define LIGHT_DMD_ROW_04_08_12_16()       { digitalWrite( PIN_DMD_B, HIGH ); digitalWrite( PIN_DMD_A, HIGH ); }
#define LATCH_DMD_SHIFT_REG_TO_OUTPUT()   { digitalWrite( PIN_DMD_SCLK, HIGH ); digitalWrite( PIN_DMD_SCLK,  LOW ); }
#define OE_DMD_ROWS_OFF()                 { digitalWrite( PIN_DMD_nOE, LOW  ); }
#define OE_DMD_ROWS_ON()                  { digitalWrite( PIN_DMD_nOE, HIGH ); }











class LedMatrix{
public:
  void LedMatrix(byte enPin1, byte enPin2, byte selectA, byte selectB, byte Lat, byte sizeMatrix);
  void LedMatrix(byte enPin1, byte enPin2, byte selectA, byte selectB, byte Lat);
  void LedMatrix();
  void scanLedMatrix(byte mode);
  void scanLedMatrix();
private:
  //  byte _size = 32;
  byte _lat, _selectA, _selectB, enPin1, _enPin2;
  byte _rowSelect;
  byte _bufferReceive[SIZE/8][SIZE];
};
#endif

