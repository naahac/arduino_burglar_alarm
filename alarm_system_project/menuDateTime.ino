void menuDateTime() {
  clearRow(0);
  clearRow(1);
  lcd.setCursor(0, 0);
  lcd.print ("DATETIME MENU");
  Serial.println("date time");

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

  }
}
