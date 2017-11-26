void initializeHighLowMenu() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print ("Set HighLow(0,1)");
  enteredPinIndex = 0;
}

void setHighLowMenu() {
  switch (results.value) {
    case IR_0:
      zones[arrayLevels[1] - 1].highToLow = 0;
      goBack();
      break;
    case IR_1:
      zones[arrayLevels[1] - 1].highToLow = 1;
      goBack();
      break;
    case IR_REW:
      goBack();
      break;
  }
}
