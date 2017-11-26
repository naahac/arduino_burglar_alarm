void checkForAlarm() {
  for (int i = 0; i < 4; i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        //Serial.println("CHECKING ENTRY_EXIT");
        if (isAlarmTurnedOn && zones[i].isTriggered != 1)
          checkEntryExit(&zones[i], digitalRead(zones[i].pin));
        break;
      case ANALOG:
        //Serial.println("CHECKING ANALOG");
        if (isAlarmTurnedOn && zones[i].isTriggered != 1)
          checkAnalog(&zones[i], analogRead(zones[i].pin));
        break;
      case DIGITAL:
        //Serial.println("CHECKING DIGITAL");
        if (isAlarmTurnedOn && zones[i].isTriggered != 1)
          checkDigital(&zones[i], digitalRead(zones[i].pin));
        break;
      case CONTINUOUS:
        //Serial.println("CHECKING CONTINUOUS");
        //We don't have to check if the alarm is turned on for continuous zone
        if (zones[i].isTriggered != 1)
          checkContinuous(&zones[i], digitalRead(zones[i].pin));
        break;
    }
  }
}

void checkAnalog(zone *zone, int value) {

}

void checkEntryExit(zone *zone, int value) {
  //TODO - if triggered -> start timer -> enable user to enter PIN
  //        if timer runs out sound the alarm
  //Serial.print("timer: "); Serial.print(zone -> timer); Serial.println(zone -> entryTime);
  if (zone -> isTriggered == 1 && zone -> timer >= zone -> entryTime) {
    //if door is opened and timer is more than entry time trigger alarm
    zone -> timer = 0;
    triggerAlarm();
    zone -> isTriggered = 0;
  } else if (value == HIGH && zone -> isTriggered == 0) {
    Serial.println("HIGH");
    zone -> timer = 0;
    zone -> isTriggered = 1;//set flag that the door was opened
  }
}

void checkDigital(zone *zone, int value) {
  if ((zone -> highToLow == 1 && value == LOW) || (zone -> highToLow == 0 && value == HIGH)) {
    triggerAlarm();
  }
}

void checkContinuous(zone *zone, bool value) {
  if ((zone -> highToLow == 1 && value == LOW) || (zone -> highToLow == 0 && value == HIGH)) {
    triggerAlarm();
  }
}

void triggerAlarm() {
  Serial.println("ALARM triggered!");
  isAlarmTriggered = 1;
  digitalWrite(ALARM_LED_PIN, HIGH);
}

void deactivateAlarm() {
  Serial.println("ALARM turned off!");
  isAlarmTurnedOn = 0;
  isAlarmTriggered = 0;
  digitalWrite(ALARM_LED_PIN, LOW);
  digitalWrite(ACTIVE_LED_PIN, LOW);
  setMainMenu();
}

void activateAlarm() {
  isAlarmTurnedOn = 1;
  showPinEnterScreen();
  digitalWrite(ACTIVE_LED_PIN, HIGH);
}

void showPinEnterScreen() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print("Enter PIN:");
}

void addPinToArray(char digit) {
  Serial.print("Adding: "); Serial.println(digit);
  enteredPin[enteredPinIndex] = digit;
  lcd.setCursor(enteredPinIndex, 1);
  lcd.print(digit);
  enteredPinIndex++;
}

void checkPin() {
  Serial.println("Check PIN");
  //find first entry exit zone
  for (int i = 0; i < 4; i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        Serial.println(enteredPin);
        Serial.println(zones[i].password);
        if (strcmp(zones[i].password, enteredPin) == 0) {
          deactivateAlarm();
        } else {
          clearRow(1);
        }
        break;
    }
  }
}

void enterPIN() {
  //TODO enter pin logic
  if (enteredPinIndex >= 4) {
    checkPin();
    enteredPinIndex = 0;
  } else {
    switch (results.value) {
      case IR_ON_OFF:
        deactivateAlarm();
        break;
      case IR_0:
        addPinToArray('0');
        break;
      case IR_1:
        addPinToArray('1');
        break;
      case IR_2:
        addPinToArray('2');
        break;
      case IR_3:
        addPinToArray('3');
        break;
      case IR_4:
        addPinToArray('4');
        break;
      case IR_5:
        addPinToArray('5');
        break;
      case IR_6:
        addPinToArray('6');
        break;
      case IR_7:
        addPinToArray('7');
        break;
      case IR_8:
        addPinToArray('8');
        break;
      case IR_9:
        addPinToArray('9');
        break;
    }
  }
}

/*bool compareArrays(char[] first, char[] second) {
  if( strcmp(test, test2) == 0)
  {
    printf("equal");
  }
  }*/

void increaseEntryExitTimer() {
  for (int i = 0; i < 4; i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        if (zones[i].isTriggered == 1) {
          zones[i].timer++;
          Serial.print(zones[i].pin);
          Serial.print(" ...... Timer runing : ");
          Serial.println(zones[i].timer);
        }
        break;
    }
  }
}
