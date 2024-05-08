#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_MASTER.hpp"
#include "LCU_function_definitions.hpp"


int main(void)
{
#ifndef USING_DOF1_CONFIG
#ifndef USING_DOF5_CONFIG
	static_assert(0==1,"neither DOF1 nor DOF5 config was used");
#endif
#endif
	//static_assert(HSE_VALUE==25'000'000,"INVALID HSE value for BOARD");
	Communication::test_order_received = new DigitalOutput(PG4);

	LCU lcu_master;

	Communication::test_order_received->turn_on();
	uint8_t unused_variable = Time::set_timeout(3000,[&](){
		Communication::test_order_received->turn_off();
	});


	while(1) {
		lcu_master.update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
