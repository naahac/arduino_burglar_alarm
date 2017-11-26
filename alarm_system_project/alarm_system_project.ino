#include <LiquidCrystal.h>
#include <IRremote.h>
#include <stdio.h>


#define IR_RCV 10
#define DEBOUNCE_TIME 5

//Alarm constants
#define BUZZER 10
#define ALARM_LED_PIN 8
#define ACTIVE_LED_PIN 9
#define PIN_ZONE_1 A5
#define PIN_ZONE_2 A4
#define PIN_ZONE_3 A3
#define PIN_ZONE_4 A2

//LCD constants
#define CONTRAST_PIN 6
#define CONTRAST_VALUE 800
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

//Zone types
#define ENTRY_EXIT 1
#define ANALOG 2
#define DIGITAL 3
#define CONTINUOUS 4


#define DEFAULT_TIME 4862
#define DEFAULT_DATE 2389
#define DAYS_OF_YEAR 365
#define DATETIME_ROW 0



typedef struct zone {
  int pin = 0;
  int type = 0;
  byte isTriggered = 0;

  //ENTRY_EXIT PARAMETERS
  char password[5] = "1234";
  int entryTime = 30;
  int exitTime = 30;
  int isTimerRunning = 0;
  volatile int timer = 0;

  //ANALOG PARAMETERS
  int analogThreshold = 0;

  //DIGITAL PARAMETERS
  byte highToLow = 0;

  //CONTINUOUS MONITORING PARAMETERS
  //byte alwaysHigh;
};

typedef struct alarm_log {
  int time;
  char message[20];
};

//Variables for date and time
volatile int current_time = DEFAULT_TIME;
int current_date = DEFAULT_DATE;

//EEPROM
int eeAdress = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//THIS IS A NEW COMMENT
IRrecv irrecv(IR_RCV);
decode_results results;

byte isAlarmTriggered = 0;
byte isAlarmTurnedOn = 0;
char enteredPin[5];
int enteredPinIndex = 0;
zone zones[4];

void setZones() {
  zones[0].pin = PIN_ZONE_3;
  zones[0].type = ANALOG;
  zones[0].highToLow = 1;
  zones[0].analogThreshold = 500;

  zones[1].pin = PIN_ZONE_1;
  zones[1].type = ENTRY_EXIT;
  zones[1].password[0] = '1';
  zones[1].password[1] = '2';
  zones[1].password[2] = '3';
  zones[1].password[3] = '4';
  zones[1].entryTime = 10;
  zones[1].exitTime = 10;

  zones[2].pin = PIN_ZONE_2;
  zones[2].type = DIGITAL;

  zones[3].pin = PIN_ZONE_4;
  zones[3].type = CONTINUOUS;
}

//Menu variables
int curr_menuSetType_index = 0;
char zoneTypes [4][16] = {"ENTRY_EXIT", "ANALOG", "DIGITAL", "CONTINUOUS"};
int zoneTypesLength = 4;

int curr_menuZone_index = 0;
int menuZoneLength = 6;
char menuZones[6][16] = {"Set Type", "Password", "wait_time", "analog_t", "active_h_l", "high_to_l"};

int curr_menu_index = 0;
int menuLength = 5;
char menu[5][16] = {"Set time", "Alarm Zone 1", "Alarm Zone 2", "Alarm Zone 3", "Alarm Zone 4"};


volatile int count = 0;

void setupIR() {
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void setupLCD() {
  //LCD contrast
  analogWrite(CONTRAST_PIN, CONTRAST_VALUE);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  setMainMenu();
} 

void setupTimer() {
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 15625; //Set the count corresponding to 1 second
  TCCR1B |= (1 << WGM12); //Turn on CTC mode
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12); //Prescale at 1024
  TIMSK1 |= (1 << OCIE1A); //Enable CTC interrupt
}

void setAlarms() {
  //pinMode(BUZZER,OUTPUT);
  pinMode(ALARM_LED_PIN, OUTPUT);
  pinMode(ACTIVE_LED_PIN, OUTPUT);

  pinMode(PIN_ZONE_1, INPUT);
  pinMode(PIN_ZONE_2, INPUT);
  pinMode(PIN_ZONE_3, INPUT);
}

void setup() {
  Serial.begin(9600);
  cli(); //Disable global interrupts
  setupTimer();
  sei(); //Enable Global Interrupts
  setupLCD();
  setupIR();
  setZones();
  setAlarms();
}

void loop() {
  decodeIR();
  checkForAlarm();
}

ISR (TIMER1_COMPA_vect) {
  current_time++;
  if (current_time >= 24 * 60 * 60) {
    current_date++;
    current_time = 0;
  }
  increaseEntryExitTimer();
}

boolean debounceRead(byte input) {
  if (digitalRead(input)) {
    delay(DEBOUNCE_TIME);
    return digitalRead(input);
  }
  return LOW;
}

