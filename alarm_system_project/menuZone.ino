void initializeZoneMenu(int zoneNumber) {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print (zoneNumber);
  lcd.setCursor(0, 1);
  lcd.print(menuZones[0]);
  arrayLevels[1]=zoneNumber;

}



void menuZone(int zoneNumber) {
  switch (results.value) {

    case IR_EQ:
          switch (curr_menuZone_index) {
        case 0:
          menu_number = MENU_ZONESUB1;
          initializeZoneSubMenu();
          //checkMENU();
          break;
        case 1:
          menu_number = MENU_ZONESUB2;
          initializeZoneSubMenu();
          //checkMENU();
          break;
        case 2:
          menu_number = MENU_ZONESUB3;
          initializeZoneSubMenu();
          //checkMENU();
          break;
        case 3:
          menu_number = MENU_ZONESUB4;
          initializeZoneSubMenu();
          //checkMENU();
          break;
        case 4:
          menu_number = MENU_ZONESUB5;
          initializeZoneSubMenu();
          //checkMENU();
          break;
        case 5:
          menu_number = MENU_ZONESUB6;
          initializeZoneSubMenu();
          //checkMENU();
          break;
      }
      break;
    case IR_REW:
      menu_number = MENU_MAIN;
      curr_menu_index = 0;
      clearRow(0);
      clearRow(1);
      lcd.setCursor(0, 0);
      //lcd.print("hh/mm - dd/mm/yy");
      printDateTime();
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
  if (curr_menuZone_index > 0)
  {
    curr_menuZone_index--;
    clearRow(1);
    lcd.setCursor(0, 1);
    lcd.print(menuZones[curr_menuZone_index]);
  }
}

void moveThroughZoneMenuPlus() {
  if (curr_menuZone_index < menuZoneLength - 1)
  {
    curr_menuZone_index++;
    clearRow(1);
    lcd.setCursor(0, 1);
    lcd.print(menuZones[curr_menuZone_index]);

  }

}
