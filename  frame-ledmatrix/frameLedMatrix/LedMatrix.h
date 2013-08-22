

#ifndef LedMatrix_h
#define LedMatrix_h

//#include "Arduino.h"
#define SIZE 32

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

