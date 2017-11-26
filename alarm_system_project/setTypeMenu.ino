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
<<<<<<< HEAD
      {

          
      }
=======

>>>>>>> 1c9b30d32b0f1b3dbc44c8fb01a7cdb8e62cc130
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
  if (curr_menuSetType_index < zoneTypesLength - 1)
  {
    curr_menuSetType_index++;
    clearRow(1);
    lcd.setCursor(0, 1);
    lcd.print(zoneTypes[curr_menuSetType_index]);

  }

}
