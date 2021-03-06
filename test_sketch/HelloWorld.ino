
/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <IRremote.h>


#define IR_RCV 13
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

void setup() {
   cli(); //Disable global interrupts
   TCCR1A = 0;
   TCCR1B = 0;
   OCR1A = 15625; //Set the count corresponding to 1 second
   TCCR1B |= (1 << WGM12); //Turn on CTC mode
   TCCR1B |= (1 << CS10);
   TCCR1B |= (1 << CS12); //Prescale at 1024
   TIMSK1 |= (1<< OCIE1A); //Enable CTC interrupt
   sei(); //Enable Global Interrupts

  //LCD contrast
  analogWrite(CONTRAST_PIN,CONTRAST_VALUE); 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  //pinMode(BUZZER,OUTPUT);

  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  //irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  
}

void loop() {

  /*if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
 
  /*tone(BUZZER,2000);
  delay(1000);
  noTone(BUZZER);
  delay(1000);*/
}

ISR (TIMER1_COMPA_vect){
  lcd.setCursor(0, 1);
  lcd.print(count);
  Serial.println(count);
  count++;
}

