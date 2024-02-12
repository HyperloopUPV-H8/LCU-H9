#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_MASTER.hpp"

int main(void)
{
	static_assert(HSE_VALUE==25'000'000,"INVALID HSE value for BOARD");
	Communication::test_order_received = new DigitalOutput(PG4);
	DigitalOutput reset_5{PB14};
	uint8_t fault_10 = DigitalInput::inscribe(PE11);
	uint8_t ready_10 = DigitalInput::inscribe(PE10);


	LCU lcu_master;

	reset_5.turn_off();
	Communication::test_order_received->turn_on();
	uint8_t unused_variable = Time::set_timeout(3000,[&](){
		Communication::test_order_received->turn_off();
	});

	while(1) {
		if(DigitalInput::read_pin_state(ready_10) == PinState::ON && DigitalInput::read_pin_state(fault_10) == PinState::ON){
			reset_5.turn_on();
		}else{
			reset_5.turn_off();
		}

		lcu_master.update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
