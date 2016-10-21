# include <Arduino.h>
#include "lib/main.h"
#include <LiquidCrystal.h>
#include "lib/timerOne.h"

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

void setPwmFrequency(int,int);

unsigned long int ms;
unsigned long int s;

void count1ms(void);
void count1s(void);

LiquidCrystal lcd(27,26,25,24,23,22);

void setup(void) {

	pinMode(9,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);

	digitalWrite(9,HIGH);
	digitalWrite(10,HIGH);
	digitalWrite(11,HIGH);
 	digitalWrite(12,HIGH);

	pinMode(28,OUTPUT);
	pinMode(29,OUTPUT);
	pinMode(30,OUTPUT);
	pinMode(31,OUTPUT);
	pinMode(32,INPUT);
	pinMode(33,INPUT);
	pinMode(34,INPUT);
	pinMode(35,INPUT);


	Timer1.initialize(1000000);
	Timer1.attachInterrupt(count1ms);

	setPwmFrequency(6,1);


	Serial.begin(9600);

	lcd.print("CFW10 CNTRL TEST!");
	delay(1000);

	return ;
}

char incomingByte = 0;

unsigned char duty = 0;

unsigned int col = 0;
unsigned int col_pressed = 0;

unsigned int row = 0;
unsigned int row_pressed = 0;

unsigned int keypress_evt_trigger = 0;
unsigned int keypress_evt_trigger_last = 0;

//int fifo_push( FIFO * fifo, FIFO * data );
//int fifo_pull( FIFO * fifo );

unsigned char keypad_decode(unsigned int col, unsigned int row);

unsigned char keypressed = NULL;

unsigned long int s_last = 0;

void loop(void) {


	if (s_last ^ s)
	{
		s_last = s;
		Serial.println(s,DEC);
	}


	int val;

	digitalWrite(28+col,HIGH);
	digitalWrite(28+col,HIGH);
	val = digitalRead(32+row);
	digitalWrite(28+col,LOW);
	digitalWrite(28+col,LOW);

	if (val == HIGH)
		{
			Serial.print("col: ");
			Serial.print(col,DEC);
			Serial.print("row: ");
			Serial.println(row,DEC);

			if ( keypress_evt_trigger_last == keypress_evt_trigger )
			{
				keypress_evt_trigger = !keypress_evt_trigger_last;
				col_pressed = col;
				row_pressed = row;
			}

		}

	if (row < 3)
	{
		row ++;
	}
	else if (row == 3 && col < 3)
	{
		col ++;
		row = 0;
	}
	else
	{
		col = 0;
		row = 0;
	}


	if ( keypress_evt_trigger_last ^ keypress_evt_trigger )
	{
				keypress_evt_trigger_last = keypress_evt_trigger;
				keypressed = keypad_decode(col_pressed,row_pressed);
				Serial.print("Key Pressed: ");
				Serial.println( (char) keypressed);
	}

//	Serial.print("col: ");
//	Serial.print(col,DEC);
//	Serial.print("row: ");
//	Serial.println(row,DEC);

	if (Serial.available() > 0)
	{
		incomingByte = Serial.read();

		Serial.print("I received: ");
		Serial.print(incomingByte);
		Serial.print(" ");
		Serial.println(incomingByte,DEC);
		switch(incomingByte)
		{
			case 100: // General Disable
				digitalWrite(9,HIGH);
				break;
			case 101: // General Enable
				digitalWrite(9,LOW);
				break;
			case 105: // Direct Rotation
				digitalWrite(10,HIGH);
				break;
			case 114: // Reverse Rotation
				digitalWrite(10,LOW);
				break;
			case 109: // Remote
				digitalWrite(11,LOW);
				break;
			case 108: // Local
				digitalWrite(11,HIGH);
				break;
			case 103: // Start
				digitalWrite(12,LOW);
				break;
			case 112: // Stop
				digitalWrite(12,HIGH);
				break;
			case 43:
				duty ++;
				analogWrite(6,duty);
				Serial.print("Duty: ");
				Serial.println(duty, DEC);
				break;
			case 45:
				duty --;
				analogWrite(6,duty);
				Serial.print("Duty: ");
				Serial.println(duty, DEC);
				break;
			default: break;
		}

	}

	return ;
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

unsigned char keypad_decode( unsigned int col, unsigned int row)
{

	switch(	0x10 << col | 0x01 << row )
	{
		case 0x11: // 0b00010001
			return '1';
		case 0x12: // 0b00010010
			return '2';
		case 0x14: // 0b00010100
			return '3';
		case 0x18: // 0b00011000
			return 'A';
		case 0x21:
			return '4';
		case 0x22:
			return '5';
		case 0x24:
			return '6';
		case 0x28:
			return 'B';
		case 0x41:
			return '7';
		case 0x42:
			return '8';
		case 0x44:
			return '9';
		case 0x48:
			return 'C';
		case 0x81:
			return '*';
		case 0x82:
			return '0';
		case 0x84:
			return '#';
		case 0x88:
			return 'D';
		default: return 0;
	}

	return 0;
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
