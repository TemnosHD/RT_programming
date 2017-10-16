#include "GPIO.h"

class task{
public:
    	task(int pinnumber){
		(this->pin) = init_gpio(pinnumber);
		this->pinstatus = 0;
	};
	
	void start_function(){
		if (this->pinstatus){
			setiopin(this->pin, 0);
			this->pinstatus = 0;
		}else{
			setiopin(this->pin, 1);
			this->pinstatus = 1;
		}
	};
private:
    	FILE *pin;
	bool pinstatus;
};
