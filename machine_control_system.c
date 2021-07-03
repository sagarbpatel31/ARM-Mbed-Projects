#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6
#define BUTTON_3 p7
#define BUTTON_4 p8

#define LED_RED p9
#define LED_YELLOW p10
#define LED_BLUE p11
#define LED_WHITE p12

DigitalIn strtbtn(BUTTON_1);
DigitalIn stopbtn(BUTTON_2);
DigitalIn guardbtn(BUTTON_3);
DigitalIn tempbtn(BUTTON_4);

DigitalOut readyled(LED_RED);
DigitalOut runningled(LED_YELLOW);
DigitalOut faultled(LED_BLUE);
DigitalOut excessled(LED_WHITE);

int main()
{
	while(1)
	{
		
		while (guardbtn==1 && tempbtn==0)
		{
			
			runningled=0;
			faultled=0;
			excessled=0;
			readyled!=readyled;
			wait(0.2);
		}
			readyled=1;
			while(strtbtn==1)
			{
					wait(0.01);
			}
			while((guardbtn==1)&&(tempbtn==0)&&(stopbtn==0))
			{
				readyled=0;
				runningled=1;
				wait(0.2);
			}
			if(guardbtn==0)
			{
				runningled=0;
				faultled=1;
				wait(0.5);
				faultled=0;
			}
			if(tempbtn==1)
			{
				runningled=0;
				excessled=1;
				wait(0.5);
				excessled=0;
			}
			if(stopbtn==1)
			{
				runningled=0;
			}
	}
	return 0;
}
