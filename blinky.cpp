

#include "rodos.h"
#include <stdio.h>
#include "hal.h"
#include <stdlib.h>

#define LED_GREEN GPIO_060
#define LED_ORANGE GPIO_061
#define LED_RED GPIO_062
#define LED_BLUE GPIO_063

#define CONTROL_UART UART_IDX3
#define BAUDRATE 115200

static Application module01("Blinky", 2000);

//pinbelegung
HAL_GPIO redLed(LED_RED);
HAL_GPIO greenLed(LED_GREEN);
HAL_GPIO blueLed(LED_BLUE);
HAL_GPIO orangeLed(LED_ORANGE);
HAL_UART u(CONTROL_UART);



//zeitvariablen und ein/aus

volatile int rTime = 1;
volatile int gTime = 1;
volatile int bTime = 1;
volatile int oTime = 1;
bool rBool = true;
bool gBool = true;
bool bBool = true;
bool oBool = true;

int length = 0;
int length2 = 0;
int writeLength = 30;





class Red : public Thread{
char id;
const char *out;
public:
  Red(char name){
		id = name;
		out = "running";
	}


void init(){
	redLed.init(true,1);
	redLed.setPins(0);

}

void run(){
	if(rBool){
		while(1){
			redLed.setPins(1);
			suspendCallerUntil(NOW() + rTime*SECONDS);
			redLed.setPins(0);
			suspendCallerUntil(NOW() + rTime*SECONDS);

		}
	}
}

};

Red r('r');



class Green : public Thread{
char id;
public:
	Green(char name){
		id = name;
	}


void init(){
	greenLed.init(true,1);
	greenLed.setPins(0);
}

void run(){
	if(gBool){
		while(1){
			greenLed.setPins(1);
			suspendCallerUntil(NOW() + gTime*SECONDS);
			greenLed.setPins(0);
			suspendCallerUntil(NOW() + gTime*SECONDS);

		}
	}
}

};

Green g('g');



class Blue : public Thread{
char id;
public:
	Blue(char name){
		id = name;
	}


void init(){
	blueLed.init(true,1);
	blueLed.setPins(0);
}

void run(){
	if(bBool){
		while(1){
			blueLed.setPins(1);
			suspendCallerUntil(NOW() + bTime*SECONDS);
			blueLed.setPins(0);
			suspendCallerUntil(NOW() + bTime*SECONDS);

		}
	}
}

};

Blue b('b');




class Orange : public Thread{
char id;
public:
	Orange(char name){
		id = name;
	}


void init(){
	orangeLed.init(true,1);
	orangeLed.setPins(0);
}

void run(){
	if(oBool){
		while(1){
			orangeLed.setPins(1);
			suspendCallerUntil(NOW() + oTime*SECONDS);
			orangeLed.setPins(0);
			suspendCallerUntil(NOW() + oTime*SECONDS);

		}
	}
}

};

Orange o('o');



class con : public Thread{
char id;
char buffer[1];
char buffer2[1];
int get;
const char *r;
const char *g;
const char *b;
const char *o;

public:
	con(char name){
		id = name;
		get = 0;
		r = "switching red";
		g = "switching green";
		b = "switching blue";
		o = "switching orange";
	}


void init(){
	u.init(BAUDRATE);


}

void run(){
	while(1){
		length = u.read(buffer,1);
		suspendCallerUntil(NOW() + 10*MILLISECONDS);
		length2 = u.read(buffer2,1);
		suspendCallerUntil(NOW() + 10*MILLISECONDS);


		if(length != 0){
			switch(buffer[0]){
			case 'R': rTime = buffer2[0] - 48;
					u.write(r,writeLength);
				break;
			case 'G': gTime = buffer2[0] - 48;
					u.write(g,writeLength);
				break;
			case 'B': bTime = buffer2[0] - 48;
					u.write(b,writeLength);
				break;
			case 'O': oTime = buffer2[0] - 48;
					u.write(o,writeLength);
				break;

			}
		}
	}
}

};

con bla('c');

