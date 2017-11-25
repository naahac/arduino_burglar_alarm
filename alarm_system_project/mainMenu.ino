void mainMENU() {


  switch (results.value) {

    case IR_EQ:
      if (curr_menu_index == 0)
      {

        menu_number = MENU_DATETIME;

        checkMENU();

      }
      else if (curr_menu_index == 1) {
        menu_number = MENU_ZONE1;

        checkMENU();
      }
      else if (curr_menu_index == 2) {
        menu_number = MENU_ZONE2;

        checkMENU();
      }
      else if (curr_menu_index == 3) {
        menu_number = MENU_ZONE3;

        checkMENU();
      }
      else if (curr_menu_index == 4) {
        menu_number = MENU_ZONE4;

        checkMENU();
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
