#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_MASTER.hpp"

int main(void)
{
	static_assert(HSE_VALUE==25'000'000,"INVALID HSE value for BOARD");
	Communication::test_order_received = new DigitalOutput(PG4);
	LCU lcu_master;
	Communication::test_order_received->turn_on();
	Time::set_timeout(1000,[&](){
		Communication::test_order_received->turn_off();
	});
	Communication comms;
	while(1) {
		lcu_master.update();
		//Communication.send_pwm_data(0, 50);
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
