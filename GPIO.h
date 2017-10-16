#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

// General purpose error message
// A real system would probably have a better error handling method...
static void panic(char *message)
{
	fprintf(stderr,"Fatal error: %s\n", message);
	exit(1);
}

// Initialize a GPIO pin in Linux using the sysfs interface
FILE *init_gpio(int gpioport)
{
	// Export the pin to the GPIO directory
	FILE *fp = fopen("/sys/class/gpio/export","w");
	fprintf(fp,"%d",gpioport);
	fclose(fp);

	// Set the pin as an output
	char filename[256];
	sprintf(filename,"/sys/class/gpio/gpio%d/direction",gpioport);
	fp = fopen(filename,"w");
	if(!fp){
		panic("Could not open gpio file");
	}
	fprintf(fp,"out");
	fclose(fp);

	// Open the value file and return a pointer to it.
	sprintf(filename,"/sys/class/gpio/gpio%d/value",gpioport);
	fp = fopen(filename,"w");
	if(!fp){
		panic("Could not open gpio file");
	}
	return fp;
}

// to the specified value. Uses the sysfs GPIO interface.
void setiopin(FILE *fp, int val)
{
	fprintf(fp,"%d\n",val);
	fflush(fp);
}
