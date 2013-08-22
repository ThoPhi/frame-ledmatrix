//#include <SPI.h>
#include "font.h"
#define MATRIX_SIZE  32
////////// PIN DEFINATION //////////
//SPI Pins for led matrix screen
#define LAT 10
#define SelectA 6
#define SelectB 7
#define enPin1  8
#define enPin2  9

////////// STATE DEFINATION //////////
#define DONOTHING 0
#define STATE_WAIT_START1  1
#define STATE_WAIT_START2  2
#define STATE_RECEIVE_POSITION 3
#define STATE_RECEIVING  4
#define STATE_WAIT_END  5
#define SCAN 10
#define GETUART 20

#define TIMEOUT_INTERVAL  800  //in ms
////////// MATRIX LED VARIABLE //////////
byte Select;
// Variable for control time
long currentMillis;
long startTransferTime;
long startIdleTime;
long millisStart;
byte x,y;
byte buffer[MATRIX_SIZE][MATRIX_SIZE];
byte bufferReceive[MATRIX_SIZE/8][MATRIX_SIZE] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

byte outarr[8];  
void convert(byte character){
  byte inarr[6];

  byte i,j;  
  if(character >= 'A' && character <= 'Z'){
    character -= 'A';
    for(i=0;i<6;i++) inarr[i] = font[character][i];
  }
  else Serial.println("error: character must from A to Z");
  for(i=0;i<8;i++) outarr[i] = 0;
  for(i=0;i<8;i++)
    for(j=0;j<6;j++){
      outarr[i] |= (inarr[j] >>i)%2;
      outarr[i] = outarr[i]<<1;
    }
  //return outarr;
}

//void convert2(byte character){
//  byte inarr[6];
//  byte i,j,len,tmp;
//  if(character >=40 && character <= 125){
//    character -= 40;  //diem bat dau
//tmp = tahoma6x8[character][0];
//len = tmp>6? 6:tmp;
//  for(i=1;i<=len;i++) inarr[i] = tahoma6x8[character][i];  //chep vao buffer
//  
//  for(i=0;i<8;i++) outarr[i] = 0;
//  for(i=0;i<8;i++)
//    for(j=0;j<6;j++){
//      outarr[i] |= (inarr[j] >>i)%2;
//      outarr[i] = outarr[i]<<1;
//    }
//    
//  }
//  else Seria;.print("error: character out of range");
//}

byte rowSelect =0;
// Variables for data flow control
unsigned int countByte;
byte stateComunication;
byte i,j,k;
unsigned int tmpCountByte = 0;
byte arr[8];

/*********** SETUP ***********/
// Setup pinMode
// setup init value for matrix led screen
/*****************************/
void setup(){
  // init for control led matrix screen


  hardware_config();

  serial_config();
  //  for(i=0;i<4;i++)
  //    for(j=0;j<16;j++){
  //      bufferReceive[i][j] = i*16+ j;
  //    }
  //bufferReceive[0][0][2][0] = 0xfa;
  //  stateComunication = STATE_WAIT_START1;
  //  startIdleTime = millis();

  convert('B');
  //arr = convert('B');
  for(byte i=0;i<8;i++){
    //bufferReceive[0][i] = (convert('B'))[i];
    bufferReceive[0][i] = outarr[i]; 
  }
}

/*********** LOOP ***********/
//
//
/*****************************/
void loop(){
  //scan led each interval time
  if((millis()- currentMillis) > 1){
    currentMillis = millis();
    scanLed();    
  }

  serial_comunication();

  if((millis() - startIdleTime) > 300000){
    fill(0xff);    
  }
}

void matrix_get(){
  byte i,j,k,tmp;
  for(i=0;i<MATRIX_SIZE/8;i++)
    for(j=0;j<MATRIX_SIZE;j++)
      for(k=0;k<8;k++)
      {
        tmp = bitRead(bufferReceive[i][j],7-k);//>>(7-k))%2;
        buffer[i*8 + k][j] = tmp;//((bufferReceive[i/8][i]) >> (7- (i%8)))%2;
      }
}

void print_buffer(){
  byte i,j;
  Serial.println("print buffer");
  for(i=0;i<MATRIX_SIZE;i++){
    for(j=0;j<MATRIX_SIZE;j++){
      Serial.print(buffer[j][i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void matrix_set(){
  byte i,j,k,tmp;
  for(i=0;i<MATRIX_SIZE/8;i++)
    for(j=0;j<MATRIX_SIZE;j++)
      bufferReceive[i][j] = 0;
  for(i=0;i<MATRIX_SIZE/8;i++)
    for(j=0;j<MATRIX_SIZE;j++)
      for(k=0;k<8;k++)
      {
        bufferReceive[i][j] <<1;
        bufferReceive[i][j] |= buffer[i*8 + k][j];
//bitWrite(bufferReceive[i][j],k,buffer[i*8+7-k][j]);
      }
}

void print_bufferReceive(){
  byte i,j;
  Serial.println("print bufferReceive");

  for(j=0;j<MATRIX_SIZE;j++){
    for(i=0;i<MATRIX_SIZE/8;i++){
      Serial.print(bufferReceive[i][j],BIN);
      Serial.print("\t\t");
    }
    Serial.println();
  }
}

void gotoxy(byte xVal, byte yVal){
  if(xVal<MATRIX_SIZE  && yVal < MATRIX_SIZE){
    x = xVal;
    y = yVal;
  }
}

void rectangle(byte width, byte lenght){
  byte i,j;
  for(i=x;i<(x+width);i++)
  for(j=y;j<(y+lenght);j++){
    if(i==x || j ==y){
      buffer[i][j] = 1;
    }
  }
}

void settext(String text){
  
}
