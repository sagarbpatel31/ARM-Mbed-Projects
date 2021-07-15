#include "mbed.h"

#define SPEAKER p21
#define RED_LED p22
#define YELLOW_LED p23
#define BLUE_LED p24
#define AIN1 p15
#define AIN2 p16

// Define the frequency of basic music notes
# define Do     0.5
# define Re     0.45
# define Mi     0.4
# define Fa     0.36
# define So     0.33
# define La     0.31
# define Si     0.3
# define No     0 

// Define the beat length (e.g. whole note, half note) 
# define b1     0.5
# define b2     0.25
# define b3     0.125
# define b4     0.075

// Define the musical piece
float note[] = {Mi,No,Mi,No,Mi,No, Mi,No,Mi,No,Mi,No, Mi,No,So,No,Do,No,Re,No,Mi,No, Fa,No,Fa,No,Fa,No,Fa,No, Fa,No,Mi,No,Mi,No,Mi,No,Mi,No, Mi,No,Mi,No,Re,No,Mi,No,Mi, Re,No,So,No};
float beat[] = {b3,b3,b3,b3,b2,b2, b3,b3,b3,b3,b2,b2, b3,b3,b3,b3,b3,b3,b3,b3,b2,b1, b3,b3,b3,b3,b3,b3,b3,b3, b3,b3,b3,b3,b3,b3,b4,b4,b4,b4, b4,b4,b4,b4,b4,b4,b2,b4,b1, b1,b3,b2,b1};

// Define the analog inputs
AnalogIn Volume(AIN1);
AnalogIn Speed(AIN2);

// Define the PWM output for the speaker
PwmOut Speaker(SPEAKER);

// Define the PWM output for the LED
PwmOut rled(RED_LED);
PwmOut yled(YELLOW_LED);
PwmOut bled(BLUE_LED);

// Define the time ticker
Ticker timer;

// Static variable
static int k;
static float volume;
static float speed;


/*----------------------------------------------------------------------------
 Interrupt Service Routine
 *----------------------------------------------------------------------------*/

//Define the ticker ISR
void timer_ISR(){

	/*
	The time ticker ISR will be periodically triggered after every single note
		+ Update the PWM frequency to the next music note
		+ Update beat length for the next music note (reconfigure the tick interrupt time)
		+ Update the colour of the RGB LEDs to reflect the melody changing
		+ The inputs from the two potentiometers will be used to adjust the volume and the speed
	*/

	if (k<(sizeof(note)/sizeof(int))){
		
		// If statement to test if the note array is currently indexed to a silent note
		if(note[k]==No)
		{
		    Speaker=0;
		}
		else
		{
		    Speaker.period(0.01*note[k]);
		    Speaker=volume;
		}

		k++;
			
		// Set the time for the next ticker interrupt, this is determined by the default music beat and the potentiometer
		timer.attach(&timer_ISR,((beat[k]/2)+(speed/2)));
			
		// RGB LED indicator
    	rled=note[k];
    	yled=Speaker;
    	bled=beat[k];
    
	// Else statement to set k and the speaker to 0 to restart the melody
	} else {
	    k=0;
	    Speaker=0;
	}
}

int main() {

	// Initialize the time ticker and set k to 0
	timer.attach(&timer_ISR,0.1);

    while (1) {

        // Update the value of the volume and the speed 
		volume=Volume.read();
		speed=Speed.read();

		wait_ms(100);
	}
}
