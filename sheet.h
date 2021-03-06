#include <pigpio.h>
#include <stdio.h>
#include <time.h>

#include "pin.h"

#define RETRACTPOS 0
#define DEPLOYPOS 100

#define SPEED_MAXFWRD 100
#define SPEED_FORWARD 147
#define SPEED_NOMINAL 150
#define SPEED_BACKWARD 153
#define SPEED_MAXBKWD 200

extern int encoderPos;

void delay(int ms) {
	long pause = ms*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	
	while (now - then < pause)
		now = clock();
}

void moveto(int position) {
	if (encoderPos < position){
		for (int speed = SPEED_NOMINAL; speed <= SPEED_FORWARD; speed++){
			gpioPWM(PIN_MOTOR, speed);
			delay(50);
		}
		while (encoderPos < position) {
				printf(NULL);
		}
	}
	else if (encoderPos > position){
		for (int speed = SPEED_NOMINAL; speed >= SPEED_BACKWARD; speed++){
			gpioPWM(PIN_MOTOR, speed);
			delay(50);
		}
		while (encoderPos > position) {
				printf(NULL);
		}
	}
	gpioPWM(PIN_MOTOR, SPEED_NOMINAL);
}

void decode(int pin, int level, uint32_t tick) {
	if (level == 1){
		char bState = gpioRead(PIN_ENCB);
		if (bState == 0) //clockwise (negative) rotation
			encoderPos--;
		if (bState == 1) //counterclockwise (positive) rotation
			encoderPos++;
	}
}

