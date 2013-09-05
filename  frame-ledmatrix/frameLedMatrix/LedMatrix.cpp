#include "LedMatrix.h"


byte bufferReceive[SIZE/8][SIZE] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

LedMatrix::LedMatrix(byte enPin1, byte enPin2, byte selectA, byte selectB, byte lat, byte sizeMatrix){
  _lat = lat;
  _selectA = selectA;
  _selectB = selectB;
  _enPin1 = enPin1;
  _enPin2 = enPin2;
  _size = sizeMatrix;
  pinMode(lat, OUTPUT);  // lat pin of SPI
  digitalWrite(lat,LOW);
  pinMode(selectA,OUTPUT);  // two select pins to select row display
  digitalWrite(selectA,LOW);
  pinMode(selectB, OUTPUT);
  digitalWrite(selectB,LOW);
  pinMode(enPin1,OUTPUT);  //
  digitalWrite(enPin1,LOW);
  pinMode(enPin2,OUTPUT);  //
  digitalWrite(enPin2,LOW);
  SPI.begin();
}

LedMatrix::LedMatrix(byte enPin1, byte enPin2, byte selectA, byte selectB, byte lat){
  _lat = lat;
  _selectA = selectA;
  _selectB = selectB;
  _enPin1 = enPin1;
  _enPin2 = enPin2;
  pinMode(lat, OUTPUT);  // lat pin of SPI
  digitalWrite(lat,LOW);  
  pinMode(selectA,OUTPUT);  // two select pins to select row display
  digitalWrite(selectA,LOW);
  pinMode(selectB, OUTPUT);
  digitalWrite(selectB,LOW);
  pinMode(enPin1,OUTPUT);  //
  digitalWrite(enPin1,LOW);
  pinMode(enPin2,OUTPUT);  //
  digitalWrite(enPin2,LOW);
  SPI.begin();
}

LedMatrix::LedMatrix(){
  _lat = 10;
  _selectA = 6;
  _selectB = 7;
  _enPin1 = 8;
  _enPin2 = 9;
  pinMode(_lat, OUTPUT);  // lat pin of SPI
  digitalWrite(_lat,LOW);
  pinMode(_selectA,OUTPUT);  // two select pins to select row display
  digitalWrite(_selectA,LOW);
  pinMode(_selectB, OUTPUT);
  digitalWrite(_selectB,LOW);
  pinMode(_enPin1,OUTPUT);  //
  digitalWrite(_enPin1,LOW);
  pinMode(_enPin2,OUTPUT);  //
  digitalWrite(_enPin2,LOW);
  SPI.begin();
}

LedMatrix::scan_led(){
  byte tmp = _rowSelect %4;
  digitalWrite(_lat,LOW);
  digitalWrite(_enPin2,LOW);
  digitalWrite(_enPin1,LOW);
  if(_rowSelect <4){
    for(j=0;j<16;j++){
      SPI.transfer(~bufferReceive[j/4][((15-j)%4)*4 + tmp]);
    }
    digitalWrite(SelectB,rowSelect%2);
    digitalWrite(SelectA,rowSelect/2);
    digitalWrite(LAT, HIGH);
    digitalWrite(enPin1,HIGH);
  }
  else{
    for(j=0;j<16;j++){
      SPI.transfer(~bufferReceive[j/4][((15-j)%4)*4 + tmp + 16]);
    }
    digitalWrite(SelectB,tmp%2);
    digitalWrite(SelectA,tmp/2);
    digitalWrite(LAT, HIGH);
    digitalWrite(enPin2,HIGH);
  }
  rowSelect = ((rowSelect+1)%8);
}

LedMatrix::fill_led(byte mask){

}


