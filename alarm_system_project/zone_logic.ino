void checkForAlarm() {
  for (int i = 0; i < 4; i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        if (isAlarmTurnedOn && zones[i].isTriggered != 1)
          checkEntryExit(&zones[i], digitalRead(zones[i].pin));
        break;
      case ANALOG:
        if (isAlarmTurnedOn && zones[i].isTriggered != 1)
          checkAnalog(&zones[i], analogRead(zones[i].pin));
        break;
      case DIGITAL:
        if (isAlarmTurnedOn && zones[i].isTriggered != 1) {
          checkDigital(&zones[i], digitalRead(zones[i].pin));
        }
        break;
      case CONTINUOUS:
        //We don't have to check if the alarm is turned on for continuous zone
        if (zones[i].isTriggered != 1) {
          checkContinuous(&zones[i], digitalRead(zones[i].pin));
        }
        break;
    }
  }
}

void checkAnalog(zone *zone, int value) {
  if ((zone -> highToLow == 1 && value < zone -> analogThreshold) || (zone -> highToLow == 0 && value >= zone -> analogThreshold)) {
    zone -> isTriggered = 1;
    triggerAlarm();
  }
}

void checkEntryExit(zone *zone, int value) {
  //TODO - if triggered -> start timer
  //        if timer runs out sound the alarm
  //Serial.print("timer: "); Serial.print(zone -> timer); Serial.println(zone -> entryTime);
  if (zone -> isTimerRunning == 1 && zone -> timer >= zone -> entryTime) {
    //if door is opened and timer is more than entry time trigger alarm
    zone -> timer = 0;
    zone -> isTimerRunning = 0;
    Serial.println("E_E.");
    triggerAlarm();
    zone -> isTriggered = 1;
  } else if (value == HIGH && zone -> isTimerRunning == 0) {
    Serial.println("HIGH");
    zone -> timer = 0;
    zone -> isTimerRunning = 1;//set flag that the door was opened
  }
}

void checkDigital(zone *zone, int value) {
  if ((zone -> highToLow == 1 && value == LOW) || (zone -> highToLow == 0 && value == HIGH)) {
    Serial.print(zone -> highToLow); Serial.print(";"); Serial.print(value); Serial.println("Digital.");
    zone -> isTriggered = 1;
    triggerAlarm();
    saveLogToEEPROM(zone -> type);
  }
}

void checkContinuous(zone *zone, bool value) {
  if ((zone -> highToLow == 1 && value == LOW) || (zone -> highToLow == 0 && value == HIGH)) {
    Serial.println("Cont.");
    zone -> isTriggered = 1;
    showPinEnterScreen();
    isAlarmTriggered = 1;
    triggerAlarm();
    saveLogToEEPROM(zone -> type);
  }
}

void triggerAlarm() {
  Serial.println("ALARM triggered!");
  isAlarmTriggered = 1;
  digitalWrite(ALARM_LED_PIN, HIGH);
}

void resetAlarmZones() {
  for (int i = 0; i < 4; i++) {
    zones[i].isTimerRunning = 0;
    zones[i].isTriggered = 0;
  }
}

void deactivateAlarm() {
  Serial.println("ALARM turned off!");
  isAlarmTurnedOn = 0;
  isAlarmTriggered = 0;
  digitalWrite(ALARM_LED_PIN, LOW);
  digitalWrite(ACTIVE_LED_PIN, LOW);
  resetAlarmZones();
  setMainMenu();
}

void startActivationTimer() {
  long waittime = current_time + getExitTime();
  Serial.print("wait: "); Serial.println(waittime);
  exitActivationTime = waittime;
}

int getExitTime() {
  for (int i = 0; i < 4; i++) {
    if(zones[i].type == ENTRY_EXIT)
      return zones[i].exitTime;
  }
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
  if (strcmp(password, enteredPin) == 0) {
    deactivateAlarm();
  } else {
    clearRow(1);
  }
}

void enterPIN() {
  if (enteredPinIndex >= 4) {
    checkPin();
    enteredPinIndex = 0;
  } else {
    switch (results.value) {
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

void saveLogToEEPROM(int type) {
  alarm_log logEntry;
  logEntry.type = type;
  logEntry.time = current_time;
  logEntry.date = current_date;
  EEPROM.put(eeAdress, logEntry);
  eeAdress += sizeof(logEntry);
}

void increaseEntryExitTimer() {
  for (int i = 0; i < 4; i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        if (zones[i].isTimerRunning == 1) {
          zones[i].timer++;
          Serial.print(zones[i].pin);
          Serial.print(" ...... Timer runing : ");
          Serial.println(zones[i].timer);
        }
        break;
    }
  }
}

