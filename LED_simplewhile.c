#include "GPIO.h"

int main()
{
	FILE *pin0 = init_gpio(17); //'name' GPIO pin 17 pin0

	while(1){
		setiopin(pin0,1); //turn LED on
		setiopin(pin0,0); //turn LED off
	}
}
