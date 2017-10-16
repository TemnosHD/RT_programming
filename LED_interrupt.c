#include "GPIO.h"

int main()
{
	unsigned int delay = 1000000/60; // Note: Delay in us
	FILE *pin0 = init_gpio(17);

	while(1){
		usleep(delay/2); //half of the delay since on 'blink' should be 60Hz
		setiopin(pin0,1);
		usleep(delay/2);
		setiopin(pin0,0);
	}
}
