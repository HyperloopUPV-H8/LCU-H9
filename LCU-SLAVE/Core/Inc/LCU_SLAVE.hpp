#include "LDU/LDU.hpp"
#include "Communication/Communication.hpp"

class LCU{
public:
	LDU ldu_array[LDU_COUNT];
	Communication communication;

	LCU();
	void start();
	void update();

};
