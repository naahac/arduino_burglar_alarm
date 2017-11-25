void menuZone(int zoneNumber) {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print (zoneNumber);
  lcd.setCursor(0, 1);
  lcd.print(menuZone0[0]);
  Serial.println(zoneNumber);

  switch (results.value) {

    case IR_EQ:

      break;
    case IR_REW:
      menu_number = MENU_MAIN;
      curr_menu_index = 0;
      clearRow(0);
      clearRow(1);
      lcd.setCursor(0, 0);
      lcd.print("hh/mm - dd/mm/yy");
      lcd.setCursor(0, 1);
      lcd.print(menu[0]);
      break;
    case IR_MINUS:
      moveThroughZoneMenuMinus();
      break;
    case IR_PLUS:
      moveThroughZoneMenuPlus();
      break;
  }
}

  void moveThroughZoneMenuMinus() {
    if (curr_menuZone_index < menuZoneLength - 1)
    {
      curr_menuZone_index--;
      clearRow(1);
      lcd.setCursor(0, 1);
      lcd.print(menu[curr_menuZone_index]);

    }

  }

  void moveThroughZoneMenuPlus() {
    if (curr_menuZone_index < menuZoneLength - 1)
    {
      curr_menuZone_index++;
      clearRow(1);
      lcd.setCursor(0, 1);
      lcd.print(menu[curr_menuZone_index]);

    }

  }
