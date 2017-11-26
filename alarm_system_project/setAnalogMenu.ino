void initializeAnalogMenu() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print ("Set Analog Threshold");
  enteredPinIndex = 0;
}
void setAnalogMenu() {
  switch (results.value) {
    case IR_EQ:
      enteredPinIndex = 0;
      int i;
      sscanf(analogThreshold, "%d", &i);
      zones[arrayLevels[1] - 1].analogThreshold = i;
      goBack;
    case IR_REW:
      goBack();
      break;
    case IR_0:
      addAnalogToArray('0');
      break;
    case IR_1:
      addAnalogToArray('1');
      break;
    case IR_2:
      addAnalogToArray('2');
      break;
    case IR_3:
      addAnalogToArray('3');
      break;
    case IR_4:
      addAnalogToArray('4');
      break;
    case IR_5:
      addAnalogToArray('5');
      break;
    case IR_6:
      addAnalogToArray('6');
      break;
    case IR_7:
      addAnalogToArray('7');
      break;
    case IR_8:
      addAnalogToArray('8');
      break;
    case IR_9:
      addAnalogToArray('9');
      break;
  }
}

void goBack() {
  enteredPinIndex = 0;
  curr_menuZone_index = 0;
  menu_number = arrayLevels[1];
  initializeZoneMenu(arrayLevels[1]);
}

void addAnalogToArray(char digit) {
  Serial.print("Adding ANALOG: "); Serial.println(digit);
  analogThreshold[enteredPinIndex] = digit;
  lcd.setCursor(enteredPinIndex, 1);
  lcd.print(digit);
  enteredPinIndex++;
}
