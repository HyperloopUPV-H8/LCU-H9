#include "LDU/LDU.hpp"
#include "CommonData/CommonData.hpp"
#include "Communication/Communication.hpp"

class LCU{
public:
	LDU ldu_array[CommonData::LDU_COUNT];
	Communication communication;

	LCU();
	void start();
	void update();

};
