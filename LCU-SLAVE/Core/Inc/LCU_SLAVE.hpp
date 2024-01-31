#include <CommonData/CommonData.hpp>
#include <Communication/Communication.hpp>
#include <LDU/LDU.hpp>

class LCU{
public:
	Communication communication;

	LCU();
	void start();
	void update();
	void setup_configuration();

};
