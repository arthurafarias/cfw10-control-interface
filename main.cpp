// Controles do Telcado Numérico
// a 97
// b 98
// c 99
// d 100 - desabilita
// e 101
// f 102
// g 103 - gira
// h 104 - habilita
// i 105 - sentido direto
// j 106
// k 107
// l 108 - local
// m 109 - remoto
// n 110
// o 111
// p 112 - para
// q 113
// r 114 - sentido reverso
// s 115
// t 116
// u 117
// v 118
// x 119
// y 120
// z 121

// int lcdPin_rs = 27;
// int lcdPin_e = 26;
// int lcdPin_d4 = 25;
// int lcdPin_d5 = 24;
// int lcdPin_d6 = 23;
// int lcdPin_d7 = 22;
// int cfw10Pin_di1 = 9; // HIGH - General Disable; LOW - General Enable
// int cfw10Pin_di2 = 10; // HIGH - Local Mode; LOW - Remote Mode
// int cfw10Pin_di3 = 11; // HIGH - Clockwize Mode; LOW - Counter Clockwize Mode
// int cfw10Pin_di4 = 12; // HIGH - Stop; LOW - Start
// int cfw10Pin_ai1 = 3; // 255 - Full Speed; 0 - Low Speed

#include <stdint.h>

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "lib/main.h"
#include "lib/TimerOne.h"
#include "lib/CFW10.h"
#include "lib/Keypad.h"

CFW10 cfw10( 9,10,11,12,6 );
LiquidCrystal lcd( 27,26,25,24,23,22 );
Keypad keypad( 28,29,30,31,32,33,34,35 );

unsigned long int ms;
unsigned long int s;

void count1ms(void);
void count1s(void);
void keypad_callback( uint8_t col, uint8_t row );

void setup(void) {

	Serial.begin(9600);
	Serial.println("CFW10 CNTRL TEST");

	lcd.print("CFW10 CNTRL TEST");

	keypad.attachCallback(keypad_callback);

	return ;
}

void loop(void) {
	keypad.itkernel();
	return ;
}

void keypad_callback(uint8_t col, uint8_t row)
{
	char keypressed = Keypad::decode( col, row );

	Serial.print("Key Pressed: ");
	Serial.println(keypressed);

	switch(keypressed)
	{
	case '1':
		cfw10.enable();
		cfw10.setDuty(255);
		cfw10.start();
		break;
	case '2':
		cfw10.setDuty(127);
		break;
	case '3':
		cfw10.setDirection( CFW10_DIRECTION_CLOCKWIZE );
		break;
	case '4':
		cfw10.setDirection( CFW10_DIRECTION_COUNTERCLOCKWIZE );
		break;
	case '5':
		cfw10.stop();
		break;
	case '6':
		cfw10.disable();
		break;
	case '7':
		break;
	case '8':
		break;
	case '9':
		break;
	case 'A':
		break;
	case 'B':
		break;
	case 'C':
		break;
	case 'D':
		break;
	case '*':
		break;
	case '#':
		break;
	default:
		break;
	}


}

void count1ms(void)
{
	ms ++;
	if (ms % 1000)
		count1s();

	return ;
}

void count1s(void)
{
	s ++;
	return ;
}
