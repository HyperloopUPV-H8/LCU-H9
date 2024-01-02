#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_SLAVE.hpp"

int main(void)
{
	LCU lcu_slave;

	for(uint8_t i = 0; i < TEST_PWM_PACKET_AMOUNT; i++){
		float duty_cycle = 60.0;
		uint32_t frequency = 500000;
		uint8_t casted_duty_cycle_1 = (uint8_t) ( (*((uint32_t*)(&duty_cycle))) >>24);
		uint8_t casted_duty_cycle_2 = (uint8_t) ( (*((uint32_t*)(&duty_cycle))) >>16);
		uint8_t casted_duty_cycle_3 = (uint8_t) ( (*((uint32_t*)(&duty_cycle))) >>8);
		uint8_t casted_duty_cycle_4 = (uint8_t) ( (*((uint32_t*)(&duty_cycle))));
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_DUTY_BYTE+3] = casted_duty_cycle_1;
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_DUTY_BYTE+2] = casted_duty_cycle_2;
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_DUTY_BYTE+1] = casted_duty_cycle_3;
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_DUTY_BYTE] = casted_duty_cycle_4;

		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_FREQ_BYTE+3] = (frequency >> 24);
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_FREQ_BYTE+2] = (frequency >> 16);
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_FREQ_BYTE+1] = (frequency >> 8);
		SPIPacket::SPIPacketsByID[TEST_PWM_1_PACKET_ID+i]->master_data[TEST_PWM_PACKET_FREQ_BYTE] = (frequency);
	}



	while(1) {
		lcu_slave.update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
