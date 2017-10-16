#include "task.h"
#include <time.h>

class task_control_block
{
public:
	task_control_block(
			task _T,
			const int _c,
			const int _p
			)
		:T(_T), cycle(_c), priority(_p) {
		};

	bool start()
	{
		clock_gettime(CLOCK_MONOTONIC, &ts);
		
		ts.tv_nsec += cycle; 

		while(ts.tv_nsec >= 1000*1000*1000){
			ts.tv_nsec -= 1000*1000*1000;
			ts.tv_sec++;
		}
		return true;
	};

	bool ready() 
	{
		clock_gettime(CLOCK_MONOTONIC, &now);
		if (ts.tv_sec == now.tv_sec)
			return ts.tv_nsec < now.tv_nsec;
		else
			return ts.tv_sec < now.tv_sec;
	};

	bool execute()
	{
		T.start_function();

		ts.tv_nsec += cycle; 

		while(ts.tv_nsec >= 1000*1000*1000){
			ts.tv_nsec -= 1000*1000*1000;
			ts.tv_sec++;
		}

		return true;
	};

	int get_cycle(){return cycle;};
	int get_priority(){return priority;};

private:
	task T;
	const int cycle;
	const int priority;
	struct timespec ts;
	struct timespec now;
};
