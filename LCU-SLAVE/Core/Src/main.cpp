#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_SLAVE.hpp"

int main(void)
{
	//static_assert(HSE_VALUE==25'000'000);
	DigitalOutput buffer_enable{PB2};
	LCU <GUI_CONTROL, double>lcu_slave;

	buffer_enable.turn_on();
	uint8_t unused_variable = Time::set_timeout(1000,[&buffer_enable](){
		buffer_enable.turn_off();
	});

	lcu_slave.change_ldu_duty_cycle(9, 50);

	while(1) {
		lcu_slave.update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}




