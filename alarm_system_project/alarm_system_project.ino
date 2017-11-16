#include <LiquidCrystal.h>
#include <IRremote.h>

#define IR_RCV 10
#define BUZZER 10

//LCD constants
#define CONTRAST_PIN 6
#define CONTRAST_VALUE 20
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2 


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

IRrecv irrecv(IR_RCV);
decode_results results;

volatile int count = 0;

void setupIR(){
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void setupLCD(){
  //LCD contrast
  analogWrite(CONTRAST_PIN,CONTRAST_VALUE); 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Wellcome!");
}

void setupTimer(){
   cli(); //Disable global interrupts
   TCCR1A = 0;
   TCCR1B = 0;
   OCR1A = 15625; //Set the count corresponding to 1 second
   TCCR1B |= (1 << WGM12); //Turn on CTC mode
   TCCR1B |= (1 << CS10);
   TCCR1B |= (1 << CS12); //Prescale at 1024
   TIMSK1 |= (1<< OCIE1A); //Enable CTC interrupt
   sei(); //Enable Global Interrupts
}

void setup() {
  Serial.begin(9600);
  setupTimer();
  setupLCD();
  setupIR();
  //pinMode(BUZZER,OUTPUT);
}

void loop() {
  decodeIR();
}

ISR (TIMER1_COMPA_vect){
  lcd.setCursor(0, 1);
  lcd.print(count);
  //Serial.println(count);
  count++;
}

