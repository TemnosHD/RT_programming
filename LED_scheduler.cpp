
//#include "GPIO.h"
#include "TCB.h"

int main()
{
	int ns = 1000*1000*1000;

	task t1(17), t2(27), t3(22);

	task_control_block 	TCB30Hz(t1, 1*ns/30, 1), //do not use FPS -> give all tasks priority 1
				TCB25Hz(t2, 1*ns/25, 1),
				TCB24Hz(t3, 1*ns/24, 1);
	TCB30Hz.start();
	TCB25Hz.start();
	TCB24Hz.start(); //start the clocks

	while(1){
		if(TCB30Hz.ready())
			TCB30Hz.execute();
		if(TCB25Hz.ready())
			TCB25Hz.execute();
		if(TCB24Hz.ready())
			TCB24Hz.execute();
	}
}
