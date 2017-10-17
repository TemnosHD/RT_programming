#include "GPIO.h"

#include <time.h>

static void sleep_until(struct timespec *ts, int delay)
{
	ts->tv_nsec += delay; 
	//the delay is added to the current time in seconds and nanoseconds separately

	while(ts->tv_nsec >= 1000*1000*1000){ //this checks for when to increase the seconds of the struct
		ts->tv_nsec -= 1000*1000*1000;
		ts->tv_sec++;
	}
	//this could also be solved by using a modulo function but this is by far computationally more expensive and will show a elongated on period every second

	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, ts,  NULL);
	//the absolute time in ts is compared to the actual time
}

int main()
{
	struct timespec ts;

	unsigned int delay = 1000*1000*1000/60; // Note: Delay in ns
	FILE *pin0 = init_gpio(17);

	clock_gettime(CLOCK_MONOTONIC, &ts); //get the current time and write this into the struct
	//CLOCK_MONOTONIC declares the type of clock that is used.

	while(1){
		sleep_until(&ts, delay/2); //Have the delay be half as long, so the LED blinks at the full frequency instead of half the frequency
		setiopin(pin0,0);
		sleep_until(&ts, delay/2);
		setiopin(pin0,1);
	}
}
