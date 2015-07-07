#include <Arduino.h>
#include "lib/main.h"

void setup(void) {
	pinMode(13, output);
	return ;
}

void loop(void) {
	delay(500);
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	return ;
}
