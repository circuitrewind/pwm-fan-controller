////////////////////////////////////////////////////////////////////////////////
// LIBRARY DEFINITIONS
////////////////////////////////////////////////////////////////////////////////
#include <util/delay.h>
#define F_CPU (8000000)




////////////////////////////////////////////////////////////////////////////////
// DEFINE EACH OF THE PINS
////////////////////////////////////////////////////////////////////////////////
#define PIN_FAN (1)
#define PIN_12  (2)
#define PIN_25  (3)
#define PIN_50  (4)
#define PIN_MAX (8)




////////////////////////////////////////////////////////////////////////////////
// CONFIGURE ALL THE THINGS !!!
////////////////////////////////////////////////////////////////////////////////
void setup() {

  // SETUP THE JUMPER PINS
  pinMode(PIN_12,   INPUT_PULLUP);
  pinMode(PIN_25,   INPUT_PULLUP);
  pinMode(PIN_50,   INPUT_PULLUP);


  // SETUP THE PWN PIN
  pinMode(PIN_FAN,  OUTPUT);
  
  TCCR0A  = bit(COM0B1)  | bit(WGM00);
  TCCR0B  = bit(WGM02)   | bit(CS00);

  OCR0A   = 0xA0;
  OCR0B   = 0xA0;
}




////////////////////////////////////////////////////////////////////////////////
// ADJUST FAN PWM SPEED BASED ON CURRENT JUMPER CONFIGURATION
////////////////////////////////////////////////////////////////////////////////
void loop() {
  // DEFAULT PWM VALUE
  int output = 0xA0;


  // CHECK IF 12% JUMPER IS SET
  if (!digitalRead(PIN_12)) {
    output -= 0x14;
  }

  // CHECK IF 25% JUMPER IS SET
  if (!digitalRead(PIN_25)) {
    output -= 0x28;
  }

  // CHECK IF 50% JUMPER IS SET
  if (!digitalRead(PIN_50)) {
    output -= 0x50;
  }

  // UPDATE THE PWM RATE
  OCR0B = output;
  
  // ONLY READ JUMPER VALUES A FEW TIMES PER SECOND
  _delay_ms(100);
}
