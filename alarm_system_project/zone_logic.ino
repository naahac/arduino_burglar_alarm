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
        if(zones[i].isTriggered != 1)
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
  digitalWrite(LED_PIN, HIGH);
  showPinEnterScreen();
}

void showPinEnterScreen() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0,0);
  lcd.print("Enter PIN:");
}

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
