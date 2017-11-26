void mainMENU() {
  switch (results.value) {
    case IR_EQ:
      switch (curr_menu_index) {
        case 0:
          menu_number = MENU_DATETIME;
          initializeDateTimeMenu();
          break;
        case 1:
          menu_number = MENU_ZONE1;
          initializeZoneMenu(1);
          Serial.println("test");
          Serial.println(menu_number);
          
          break;
        case 2:
          menu_number = MENU_ZONE2;
          initializeZoneMenu(2);
          
          break;
        case 3:
          menu_number = MENU_ZONE3;
          initializeZoneMenu(3);
          
          break;
        case 4:
          menu_number = MENU_ZONE4;
          initializeZoneMenu(4);
          
          break;
      }
      break;
    case IR_MINUS:
      if (curr_menu_index > 0)
      {
        curr_menu_index--;
        clearRow(1);
        lcd.setCursor(0, 1);
        lcd.print(menu[curr_menu_index]);
      }
      break;
    case IR_PLUS:
      if (curr_menu_index < menuLength - 1)
      {
        curr_menu_index++;
        clearRow(1);
        lcd.setCursor(0, 1);
        lcd.print(menu[curr_menu_index]);
      }
      break;
  }
}
