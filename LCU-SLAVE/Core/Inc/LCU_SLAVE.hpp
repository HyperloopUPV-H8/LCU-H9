#include <CommonData/CommonData.hpp>
#include <Communication/Communication.hpp>
#include <LDU/LDU.hpp>

class LCU{
public:
	LDU ldu_array[LDU_COUNT];

	LCU();
	void start();
	void update();

};
