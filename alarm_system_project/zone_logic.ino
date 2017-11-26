void checkForAlarm() {
  for (int i = 0; i < sizeof(zones); i++) {
    switch (zones[i].type) {
      case ENTRY_EXIT:
        //Serial.println("CHECKING ENTRY_EXIT");
        checkEntryExit(zones[i], debounceRead(digitalRead(zones[i].pin)));
        break;
      case ANALOG:
        //Serial.println("CHECKING ANALOG");
        checkAnalog(zones[i], analogRead(zones[i].pin));
        break;
      case DIGITAL:
        //Serial.println("CHECKING DIGITAL");
        checkDigital(zones[i], debounceRead(zones[i].pin));
        break;
      case CONTINUOUS:
        //Serial.println("CHECKING CONTINUOUS");
        checkContinuous(zones[i], debounceRead(zones[i].pin));
        break;
    }
  }
}

void checkAnalog(zone zone, int value) {

}

void checkEntryExit(zone zone, bool value) {
  if (!value) {
    //Serial.println("Entry/Exit ALARM!");
  }
}

void checkDigital(zone zone, int value) {

}

void checkContinuous(zone zone, bool value) {

}
