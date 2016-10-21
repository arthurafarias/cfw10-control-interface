#ifndef CFW10_cpp_
#define CFW10_cpp_

#include "lib/CFW10.h"

void setPwmFrequency(int pin, int divisor);

CFW10::CFW10(uint8_t di1Pin, uint8_t di2Pin, uint8_t di3Pin, uint8_t di4Pin, uint8_t ai1Pin )
{

    CFW10::di1Pin = di1Pin;
    CFW10::di2Pin = di2Pin;
    CFW10::di3Pin = di3Pin;
    CFW10::di4Pin = di4Pin;
    CFW10::ai1Pin = ai1Pin;

    pinMode(di1Pin,OUTPUT);
    pinMode(di2Pin,OUTPUT);
    pinMode(di3Pin,OUTPUT);
    pinMode(di4Pin,OUTPUT);

    digitalWrite(CFW10::di1Pin, HIGH);
    digitalWrite(CFW10::di2Pin, HIGH);
    digitalWrite(CFW10::di3Pin, HIGH);
    digitalWrite(CFW10::di4Pin, HIGH);

    setPwmFrequency( CFW10::ai1Pin , 1 );

    analogWrite( CFW10::ai1Pin , 0);

}

void CFW10::setOpMode(CFW10_OPMODE mode)
{
    digitalWrite(CFW10::di3Pin, mode);
}

void CFW10::enable(void)
{
    CFW10::setOpMode( CFW10_OPMODE_REMOTE );
    digitalWrite(CFW10::di1Pin, LOW);
}

void CFW10::disable(void)
{
    CFW10::setOpMode( CFW10_OPMODE_REMOTE );
    digitalWrite(CFW10::di1Pin, HIGH);
}

void CFW10::start(void)
{
    CFW10::setOpMode( CFW10_OPMODE_REMOTE );
    digitalWrite(CFW10::di4Pin, LOW);
}

void CFW10::stop(void)
{
    CFW10::setOpMode( CFW10_OPMODE_REMOTE );
    digitalWrite(CFW10::di4Pin, HIGH);
}

void CFW10::start(CFW10_DIRECTION dir)
{
    CFW10::setOpMode( CFW10_OPMODE_REMOTE );
    digitalWrite(CFW10::di2Pin, dir);
    digitalWrite(CFW10::di4Pin, LOW);
}

void CFW10::setDirection(CFW10_DIRECTION dir)
{
    CFW10::setOpMode( CFW10_OPMODE_REMOTE );
    digitalWrite(CFW10::di2Pin, dir);
}

void CFW10::setDuty( uint8_t duty )
{
	analogWrite( CFW10::ai1Pin, duty );
}

void setPwmFrequency(int pin, int divisor) {

  byte mode;

  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

#endif
