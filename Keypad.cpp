#include <Arduino.h>
#include "lib/Keypad.h"

Keypad::Keypad( uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4, uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4 )
{

    Keypad::col[0] = col1;
    Keypad::col[1] = col2;
    Keypad::col[2] = col3;
    Keypad::col[3] = col4;

    Keypad::row[0] = row1;
    Keypad::row[1] = row2;
    Keypad::row[2] = row3;
    Keypad::row[3] = row4;

    Keypad::col_curr = 0;
    Keypad::row_curr = 0;

    Keypad::col_pressed = 0;
    Keypad::row_pressed = 0;

    pinMode(Keypad::col[0], OUTPUT);
    pinMode(Keypad::col[1], OUTPUT);
    pinMode(Keypad::col[2], OUTPUT);
    pinMode(Keypad::col[3], OUTPUT);
    pinMode(Keypad::row[0], INPUT);
    pinMode(Keypad::row[1], INPUT);
    pinMode(Keypad::row[2], INPUT);
    pinMode(Keypad::row[3], INPUT);

}

void Keypad::itkernel(void)
{

    int val;

    digitalWrite(Keypad::col[col_curr],HIGH);
    digitalWrite(Keypad::col[col_curr],HIGH);

    val = digitalRead(Keypad::row[row_curr]);

    digitalWrite(Keypad::col[col_curr],LOW);
    digitalWrite(Keypad::col[col_curr],LOW);

    if (val == HIGH)
    {

//	Serial.print("Col: ");
//	Serial.println(col_curr);
//	Serial.print("Row: ");
//	Serial.println(row_curr);

        if (Keypad::callback != NULL)
            Keypad::callback( col_curr, row_curr );
    }

    if (Keypad::row_curr < 3)
    {
        Keypad::row_curr ++;
    }
    else if (Keypad::row_curr == 3 && Keypad::col_curr < 3)
    {
        Keypad::col_curr ++;
        Keypad::row_curr = 0;
    }
    else
    {
        Keypad::col_curr = 0;
        Keypad::row_curr = 0;
    }

}

char Keypad::decode( uint8_t col, uint8_t row)
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

void Keypad::attachCallback ( void ( * callback ) (uint8_t col, uint8_t row) )
{
	if (callback != NULL)
		Keypad::callback = callback;
}
