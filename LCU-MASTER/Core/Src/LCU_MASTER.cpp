#include "LCU_MASTER.hpp"

LCU::LCU(){
	STLIB::start(MASTER_IP.string_address);
	communication.start();
}

void LCU::update(){
	STLIB::update();
}
