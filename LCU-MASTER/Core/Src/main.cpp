#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_MASTER.hpp"

int main(void)
{
	LCU lcu_master;

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