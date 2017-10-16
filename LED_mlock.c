#include "GPIO.h"

int main()
{
        // Lock memory to ensure no swapping is done.
        if(mlockall(MCL_FUTURE|MCL_CURRENT)){
                fprintf(stderr,"WARNING: Failed to lock memory\n");
        }

	FILE *pin0 = init_gpio(17); //'name' GPIO pin 17 pin0
	FILE *pin1 = init_gpio(27); //'name' GPIO pin 22 pin1
	//use two LEDs which are in opposite states. This will show a "blink" any time the program hesitates

	

	int j;
	char *tmp;

	tmp = malloc(1024*1024);
	if(!tmp){
		printf("Cannot allocate memory\n");
		exit(0);
	}

	for(j=0; j < 1024*1024; j+=1024){
		tmp[j] = 1;
	}

	while(1){
		setiopin(pin0,0); //turn LED on
		setiopin(pin1,1); //turn LED on
		for(j=0; j < 1024*1024; j+=1024){
			tmp[j] = 1;
		}
		setiopin(pin1,0); //turn LED off
		setiopin(pin0,1); //turn LED off
		for(j=0; j < 1024*1024; j+=1024){
			tmp[j] = 0;
		}
	}
}
