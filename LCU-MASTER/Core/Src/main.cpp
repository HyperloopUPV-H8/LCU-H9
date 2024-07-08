#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_MASTER.hpp"
#include "LCU_function_definitions.hpp"

void asserts();

int main(void)
{
	asserts();
	LCU lcu_master;


	while(1) {
		lcu_master.update();
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
