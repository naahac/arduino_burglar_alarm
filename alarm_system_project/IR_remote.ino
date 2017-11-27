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

void setMainMenu() {
  lcd.setCursor(0, 0);
  printDateTime();

  lcd.setCursor(0, 1);
  lcd.print(menu[0]);

  menu_number = MENU_MAIN;
}

void clearRow(int r) {
  lcd.setCursor (0, r);
  for (int i = 0; i < 16; ++i)
  {
    lcd.print(' ');
  }
}

void decodeIR() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value);
    //Serial.println(menu_number);
    if (isAlarmTurnedOn || isAlarmTriggered) {
      enterPIN();
    } else {
      switch (results.value) {
        case IR_MODE:
          startActivationTimer();
          break;
        case IR_MUTE:
          saveToEEPROM();
          break;
        default:
          checkMENU();
          break;
      }
    }
    irrecv.resume(); // Receive the next value
  }
}

bool checkForEntry() {
  for (int i = 0; i < 4; i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        if (zones[i].isTriggered == 1) {
          enterPIN();
          return true;
        }
        break;
    }
  }
  return false;
}

void checkMENU() {
  switch (menu_number) {
    case MENU_MAIN:
      mainMENU();
      break;
    case MENU_DATETIME:
      menuDateTime();
      break;
    case MENU_ZONE1:
      menuZone(1);
      break;
    case MENU_ZONE2:
      menuZone(2);
      break;
    case MENU_ZONE3:
      menuZone(3);
      break;
    case MENU_ZONE4:
      menuZone(4);
      break;
    case MENU_ZONE_TYPE:
      setTypeMenu();
      break;
    case MENU_PASSWORD:
      setPasswordMenu();
      break;
    case MENU_HIGH_LOW:
      setHighLowMenu();
      break;
    case MENU_ANALOG_THRESHOLD:
      setAnalogMenu();
      break;
    case MENU_WAIT_TIME:
      setWaitTimeMenu();
      break;
  }
}













