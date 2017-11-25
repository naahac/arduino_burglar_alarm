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


#define  MENU_MAIN 0
#define  MENU_DATETIME 1
#define  MENU_ZONE1 2
#define  MENU_ZONE2 3
#define  MENU_ZONE3 4
#define  MENU_ZONE4 5



int menu_number = MENU_MAIN;

void clearRow(int r) {
  lcd.setCursor (0, r);
  for (int i = 0; i < 16; ++i)
  {
    lcd.print(' ');
  }
}

void decodeIR() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    Serial.println(menu_number);
    checkMENU();

    irrecv.resume(); // Receive the next value
  }

}

void checkMENU() {

  if (menu_number == MENU_MAIN) {
    mainMENU();
  }
  else if (menu_number == MENU_DATETIME) {
    menuDateTime();
  }
  else if (menu_number == MENU_ZONE1) {
    menuZone(0);
  }
  else if (menu_number == MENU_ZONE2) {
    menuZone(1);
  }
  else if (menu_number == MENU_ZONE3) {
    menuZone(2);
  }
  else if (menu_number == MENU_ZONE4) {
    menuZone(3);
  }
}












