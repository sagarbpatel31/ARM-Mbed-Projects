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

//Define counters

volatile unsigned int count1;
volatile unsigned int count2;
volatile unsigned int count3;
volatile unsigned int countmax;

void updateLEDs(){
    
    led_1=0;
    led_2=0;
    led_3=0;
    
    if(count1==countmax)led_1=1;
    if(count2==countmax)led_2=1;
    if(count3==countmax)led_3=1;
}


//Define ISRs for the interrupts
void button_1_handler(){
	
	count1++;
	if(count1>countmax)countmax=count1;
	updateLEDs();
	
}

void button_2_handler(){
	
	count2++;
	if(count2>countmax)countmax=count2;
	updateLEDs();
	
}

void button_3_handler(){
	
    count3++;
    if(count3>countmax)countmax=count3;
    updateLEDs();
	
}

void button_4_handler(){
	
	led_1=0;
	led_2=0;
	led_3=0;
	
	count1=0;
	count2=0;
	count3=0;
	countmax=0;
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
		
	//Initially turn off all LEDs and set all the counters to 0
	
	button_4_handler();

	//Interrupt handlers
	
	b1.rise(&button_1_handler);
	b2.rise(&button_2_handler);
	b3.rise(&button_3_handler);
	b4.rise(&button_4_handler);

	//wait 100 ms
	while(1)
		wait_ms(100);
}
