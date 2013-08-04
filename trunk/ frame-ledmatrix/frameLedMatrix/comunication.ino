

void serial_config(){
  // init serial for comunication
  Serial.begin(115200);
  //Serial.println("Begin");  // just for test
}

void serial_comunication(){
  if(Serial.available()){
    byte tmp = Serial.read();
    switch(tmp){
    case '0':
      matrix_get();
      break;
    case '1':
      print_buffer();
      break;
    case '2':
      matrix_set();
      break; 
    case '3':
     print_bufferReceive();
      break;
    case '4':
      
      break;
    case '5':
      fill(0);
      break;
    case '6':
      fill(255);
      break;
    case '7':

      break;
    case '8':

      break;
    case '9':

      break;
    case 'A' ... 'Z':
      convert(tmp);

      for(byte i =0;i<8;i++){
        bufferReceive[tmpCountByte%4][(tmpCountByte/4)*8 + i] = outarr[i];
      }
      tmpCountByte ++;//= 8;
      if(tmpCountByte >= 16) tmpCountByte = 0;
      break;

    case ' ':   

      for(byte i =0;i<8;i++){
        bufferReceive[tmpCountByte%4][(tmpCountByte/4)*8 + i] = 0x00;//outarr[i];
      }
      tmpCountByte ++;//= 8;
      if(tmpCountByte >= 16) tmpCountByte = 0;
      break;
    }
  }
}


