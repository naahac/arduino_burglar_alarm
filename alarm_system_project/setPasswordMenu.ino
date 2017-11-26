void initializePasswordSetMenu() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print ("Set Password");
  enteredPinIndex = 0;
}
void setPasswordMenu() {
  switch (results.value) {
    case IR_REW:
      goBack();
      break;
    case IR_0:
      addPwToArray('0');
      break;
    case IR_1:
      addPwToArray('1');
      break;
    case IR_2:
      addPwToArray('2');
      break;
    case IR_3:
      addPwToArray('3');
      break;
    case IR_4:
      addPwToArray('4');
      break;
    case IR_5:
      addPwToArray('5');
      break;
    case IR_6:
      addPwToArray('6');
      break;
    case IR_7:
      addPwToArray('7');
      break;
    case IR_8:
      addPwToArray('8');
      break;
    case IR_9:
      addPwToArray('9');
      break;
  }
}

void addPwToArray(char digit) {
  Serial.print("Adding: "); Serial.println(digit);
  password[enteredPinIndex] = digit;
  lcd.setCursor(enteredPinIndex, 1);
  lcd.print(digit);
  enteredPinIndex++;
}
