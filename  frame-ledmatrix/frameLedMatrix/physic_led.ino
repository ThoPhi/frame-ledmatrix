

void hardware_config(){
  pinMode(LAT, OUTPUT);  // lat pin of SPI
  digitalWrite(LAT,LOW);
  pinMode(SelectA,OUTPUT);  // two select pins to select row display
  digitalWrite(SelectA,LOW);
  pinMode(SelectB, OUTPUT);
  digitalWrite(SelectB,LOW);
  pinMode(enPin1,OUTPUT);  //
  digitalWrite(enPin1,LOW);
  pinMode(enPin2,OUTPUT);  //
  digitalWrite(enPin2,LOW);

  // init SPI hardware for control ledmatrix screen
  SPI.begin();
}

// Hardware function 
// Controling Matrix Led Panel
// Scan and clear led screen
// Dont care anymore

/*********** SCAN_lED ***********/
//
//
/*****************************/
void scanLed(){ 
  byte tmp = rowSelect %4;

  digitalWrite(LAT,LOW);
  //for(i=0;i<4;i++)
  
  digitalWrite(enPin2,LOW);
  digitalWrite(enPin1,LOW);
  if(rowSelect <4){
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
  //  digitalWrite(enPin,LOW);
}

/*********** CLEAR_LED ***********/
//
//
/*****************************/
void fill(byte mask){
  for(i=0;i<4;i++)
    for(j=0;j<16;j++)   
      bufferReceive[i][j]= mask;       

}


