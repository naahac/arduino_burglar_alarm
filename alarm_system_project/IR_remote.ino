#define  IR_0       0xff6897
#define  IR_1       0xff30cf
#define  IR_2       0xff18e7
#define  IR_3       0xff7a85
#define  IR_4       0xff10ef
#define  IR_5       0xff38c7
#define  IR_6       0xff5aa5
#define  IR_7       0xff42bd
#define  IR_8       0xff4ab5
#define  IR_9       0xff52ad
#define  IR_MINUS   0xffe01f
#define  IR_PLUS    0xffa857
#define  IR_EQ      0xff906f
#define  IR_ON_OFF  0xffa25d
#define  IR_MODE    0xff629d
#define  IR_MUTE    0xffe21d
#define  IR_PLAY    0xffc23d
#define  IR_REW     0xff22dd
#define  IR_FF      0xff02fd

int keyToInt(int key_pressed){
  switch(key_pressed){
    case IR_0: return 0;
    case IR_1: return 1;
    case IR_2: return 2;
    case IR_3: return 3;
    case IR_4: return 4;
    case IR_5: return 5;
    case IR_6: return 6;                                         
    case IR_7: return 7;  
    case IR_8: return 8;    
    case IR_9: return 9; 
    case IR_MINUS: return 10;  
    case IR_PLUS: return 11;   
    case IR_EQ: return 12;     
    case IR_ON_OFF: return 13;     
    case IR_MODE: return 14;   
    case IR_MUTE: return 15; 
    case IR_PLAY: return 16;   
    case IR_REW: return 17;  
    case IR_FF: return 18; 
    default: return -1;     
  }
}

void IR_0_CB(){
  Serial.println("IR_0_CB");
}

void IR_1_CB(){
  Serial.println("IR_1_CB");
}

void IR_2_CB(){
  Serial.println("IR_2_CB");
}

void IR_3_CB(){
  Serial.println("IR_3_CB");
}

void IR_4_CB(){
  Serial.println("IR_4_CB");
}

void IR_5_CB(){
  Serial.println("IR_5_CB");
}

void IR_6_CB(){
  Serial.println("IR_6_CB");
}

void IR_7_CB(){
  Serial.println("IR_7_CB");
}

void IR_8_CB(){
  Serial.println("IR_8_CB");
}

void IR_9_CB(){
  Serial.println("IR_9_CB");
}

void IR_MINUS_CB(){
  Serial.println("IR_MINUS_CB");
}

void IR_PLUS_CB(){
  Serial.println("IR_PLUS_CB");
}

void IR_EQ_CB(){
  Serial.println("IR_EQ_CB");
}

void IR_ON_OFF_CB(){
  Serial.println("IR_ON_OFF_CB");
}

void IR_MODE_CB(){
  Serial.println("IR_MODE_CB");
}

void IR_MUTE_CB(){
  Serial.println("IR_MUTE_CB");
}

void IR_PLAY_CB(){
  Serial.println("IR_PLAY_CB");
}

void IR_REW_CB(){
  Serial.println("IR_REW_CB");
}

void IR_FF_CB(){
  Serial.println("IR_FF_CB");
}

void printKeyKind(int key_pressed){
  switch(key_pressed){
    case IR_0: Serial.println("0");
                   break;
    case IR_1: Serial.println("1");
                   break;
    case IR_2: Serial.println("2");
                   break;
    case IR_3: Serial.println("3");
                   break;
    case IR_4: Serial.println("4");
                   break;
    case IR_5: Serial.println("5");
                   break;
    case IR_6: Serial.println("6");
                   break;                                         
    case IR_7: Serial.println("7");
                   break;  
    case IR_8: Serial.println("8");
                   break;    
    case IR_9: Serial.println("9");
                   break; 
    case IR_MINUS: Serial.println("MINUS");
                   break;  
    case IR_PLUS: Serial.println("PLUS");
                   break;   
    case IR_EQ: Serial.println("EQ");
                   break;     
    case IR_ON_OFF: Serial.println("ON_OFF");
                   break;     
    case IR_MODE: Serial.println("MODE");
                   break;   
    case IR_MUTE: Serial.println("MUTE");
                   break; 
    case IR_PLAY: Serial.println("PLAY");
                   break;   
    case IR_REW: Serial.println("REW");
                   break;  
    case IR_FF: Serial.println("FF");
                   break;  
       default: Serial.println(key_pressed);
                   break;    
  }
}

void CBCaller(int keyInt){
  switch (keyInt){
    case 0: IR_0_CB();break;
    case 1: IR_1_CB();break;
    case 2: IR_2_CB();break;
    case 3: IR_3_CB();break;
    case 4: IR_4_CB();break;
    case 5: IR_5_CB();break;
    case 6: IR_6_CB();break;
    case 7: IR_7_CB();break;
    case 8: IR_8_CB();break;
    case 9: IR_9_CB();break;
    case 10: IR_MINUS_CB();break;
    case 11: IR_PLUS_CB();break;
    case 12: IR_EQ_CB();break;
    case 13: IR_ON_OFF_CB();break;
    case 14: IR_MODE_CB();break;
    case 15: IR_MUTE_CB();break;
    case 16: IR_PLAY_CB();break;
    case 17: IR_REW_CB();break;
    case 18: IR_FF_CB();break;
  }
}

void decodeIR(){
    if (irrecv.decode(&results)) {
        lcd.setCursor(0,0);
        lcd.print("");
      switch(results.value){
        //case IR_PLUS: tone(BUZZER,2000); break;
        //case IR_MINUS: noTone(BUZZER); break;
      }
      irrecv.resume(); // Receive the next value
    }
  
}

