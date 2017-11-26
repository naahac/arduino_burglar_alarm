void initializeZoneSubMenu() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print ("ZONE SUB MENU");
  lcd.setCursor(0, 1);
  lcd.print(zoneTypes[0]);

}
void setTypeMenu() {
  switch (results.value) {
    case IR_EQ:
      switch (curr_menuSetType_index) {
        case 0:

          zones[arrayLevels[1]-1].type = ENTRY_EXIT;
          //Serial.println(zones[arrayLevels[1]].type );
          break;
        case 1:
          zones[arrayLevels[1] - 1].type = ANALOG;
          
          break;
          
        case 2:
          zones[arrayLevels[1] - 1].type = DIGITAL;
          break;
        case 3:
          zones[arrayLevels[1] - 1].type = CONTINUOUS;
          break;
      }
      break;
    case IR_REW:
      curr_menuZone_index = 0;
      menu_number = arrayLevels[1];
      initializeZoneMenu(arrayLevels[1]);
      break;
    case IR_MINUS:
      moveThroughSetTypeMinus();
      break;
    case IR_PLUS:
      moveThroughSetTypePlus();
      break;
  }
}

void moveThroughSetTypeMinus() {
  if (curr_menuSetType_index > 0)
  {
    curr_menuSetType_index--;
    clearRow(1);
    lcd.setCursor(0, 1);
    lcd.print(zoneTypes[curr_menuSetType_index]);
  }
}

void moveThroughSetTypePlus() {
  if (curr_menuSetType_index < zoneTypesLength - 1)
  {
    curr_menuSetType_index++;
    clearRow(1);
    lcd.setCursor(0, 1);
    lcd.print(zoneTypes[curr_menuSetType_index]);

  }

}
