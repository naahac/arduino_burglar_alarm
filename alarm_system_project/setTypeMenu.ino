void setTypeMenu() {
  switch (results.value) {

    case IR_EQ:
      {
        clearRow(0);
        clearRow(1);
        lcd.setCursor(0, 0);
        lcd.setCursor(0, 1);
      }
      break;
    case IR_REW:
      menu_number = MENU_MAIN;
      curr_menuZone_index = 0;
      void initializeZoneMenu(int zoneNumber);
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
  if (curr_menuSetType_index < menuZoneLength - 1)
  {
    curr_menuSetType_index++;
    clearRow(1);
    lcd.setCursor(0, 1);
    lcd.print(zoneTypes[curr_menuSetType_index]);

  }

}
