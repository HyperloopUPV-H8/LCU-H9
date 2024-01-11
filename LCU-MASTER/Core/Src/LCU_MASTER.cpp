#include "LCU_MASTER.hpp"

LCU::LCU(){
	Communication::init();
	STLIB::start(MASTER_IP.string_address);
	Communication::start();
}

void LCU::update(){
	STLIB::update();
	SPI::packet_update();
}
