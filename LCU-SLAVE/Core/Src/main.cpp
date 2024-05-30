#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_SLAVE.hpp"
#include "LCU_functions_definition.hpp"


void asserts();

int main(void)
{
	asserts();
	LCU <RUNNING_MODE, ARITHMETIC_MODE>lcu_slave;

	while(1) {
		lcu_slave.update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}


void asserts(){
	//static_assert(HSE_VALUE==25'000'000,"INVALID HSE value for BOARD");
}

