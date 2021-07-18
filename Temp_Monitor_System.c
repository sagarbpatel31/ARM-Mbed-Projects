#include "mbed.h"

DigitalOut led(p5);
PwmOut speaker(p21);
AnalogIn level(p15);
AnalogIn temp(p16);

float lival,hival,i;

int main()
{
	while(1)
	{
		speaker=0.5;
		while(level.read()<0.75)
		{
			led=!led;
			for(i=0;i<1;i+=0.05)
			{
				speaker.period(0.01-(0.008*i));
				wait_ms(50);
			}
		}
		led=0;
		if(temp.read()<0.33)
		{
			hival=0.005;
			lival=1;
		}
		if(temp.read()>0.66)
		{
			hival=0.001;
			lival=0.005;
		}
		if((temp.read()>0.33)&&(temp.read()<0.66))
		{
			hival=0.002;
			lival=0.002;
		}
		speaker.period(hival);
		wait_ms(500);
		speaker.period(lival);
		wait_ms(500);

	}
	return 0;
}
