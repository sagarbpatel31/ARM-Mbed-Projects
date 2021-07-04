#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6 
#define BUTTON_3 p7 
#define BUTTON_4 p8 

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

//Define outputs

DigitalOut led_1(RED_LED);
DigitalOut led_2(YELLOW_LED);
DigitalOut led_3(BLUE_LED);


//Define interrupt inputs

InterruptIn b1(BUTTON_1);
InterruptIn b2(BUTTON_2);
InterruptIn b3(BUTTON_3);
InterruptIn b4(BUTTON_4);


//Define ISRs for the interrupts
void button_1_handler(){
	
	led_1=!led_1;
	
}

void button_2_handler(){
	
	led_2=!led_2;
	
}

void button_3_handler(){
	
	led_3=!led_3;
	
}

void button_4_handler(){
	
	led_1=1;
	led_2=1;
	led_3=1;
	
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
		
	//Initially turn off all LEDs
    led_1=0;
    led_2=0;
    led_3=0;

	//Interrupt handlers
	//Attach the address of the ISR to the rising edge
	
	b1.rise(&button_1_handler);
	b2.rise(&button_2_handler);
	b3.rise(&button_3_handler);
	b4.rise(&button_4_handler);
	
	
	//wait 100 ms
	while(1)
		wait_ms(100);
}

