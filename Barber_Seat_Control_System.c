#include "mbed.h"

InterruptIn adult_in(p5);
InterruptIn child_in(p6);
InterruptIn fire_alarm(p7);

DigitalOut no_entry(p8);
DigitalOut Barb1_ch(p9);
DigitalOut Barb2_ch(p10);
DigitalOut Barb3_ch(p11);
DigitalOut Wall_clk(p12);

BusOut Seating_line(p13,p14,p15,p16,p17,p18,p19,p20);

int Time_ch1,Time_ch2,Time_ch3,Seats_pattern,no_child,no_adult;


void adult_in_handler()
{
	if((no_child+no_adult)<8)
	{
		no_adult++;
		Seats_pattern=Seats_pattern<<1;
		Seats_pattern=Seats_pattern|01;
	}
	else
	{
		no_entry=1;
		wait_ms(40);
		no_entry=0;
	}
}

void child_in_handler()
{
	if((no_child+no_adult)<7)
	{
		no_child=no_child+2;
		Seats_pattern=Seats_pattern<<2;
		Seats_pattern=Seats_pattern|03;
	}
	else
	{
		no_entry=1;
		wait_ms(40);
		no_entry=0;
	}
}

void fire_alarm_handler()
{
	no_entry=1;
	Barb1_ch=Barb2_ch=Barb3_ch=0;
	while(Seats_pattern!=0)
	{
		Seats_pattern=Seats_pattern>>1;
		Seating_line=Seats_pattern;
		wait_ms(600);
	}
	no_child=0;
	no_adult=0;
	wait_ms(20);
	no_entry=0
}


int main()
{
	adult_in.rise(&adult_in_handler);
	child_in.rise(&child_in_handler);
	fire_alarm.rise(&fire_alarm_handler);

	while(1)
	{
		if(Barb1_ch==1)
		{
			Time_ch1--;
			if(Time_ch1==0)
			{
				Barb1_ch=0;
			}
		}
		else if(no_adult!=0)
		{
			Barb1_ch=1;
			no_adult--;
			Seats_pattern=Seats_pattern>>1;
			Time_ch1=12;
		}
		if(Barb2_ch==1)
		{
			Time_ch2--;
			if(Time_ch2==0)
			{
				Barb2_ch=0;
			}
		}
		else if(no_adult!=0)
		{
			Barb2_ch=1;
			no_adult--;
			Seats_pattern=Seats_pattern>>1;
			Time_ch2=12;
		}
		if(Barb3_ch==1)
		{
			Time_ch3--;
			if(Time_ch3==0)
			{
				Barb3_ch=0;
				no_child--;
				Seats_pattern=Seats_pattern>>1;
			}

		}
		else if(no_child!=0)
		{
			Barb3_ch=1;
			no_child--;
			Seats_pattern=Seats_pattern>>1;
			Time_ch3=12;
		}
		Seating_line=Seats_pattern;
		wait_ms(1000);
		Wall_clk=!Wall_clk;
	}
	return 0;
}
