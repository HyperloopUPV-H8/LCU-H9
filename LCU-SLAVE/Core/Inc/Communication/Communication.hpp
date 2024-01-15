#pragma once

#include <CommonData/CommonData.hpp>
#include "SPI/SPI.hpp"


class Communication{
public:
	static uint8_t spi_id;
	static SPIPacket* test_pwm_packets[TEST_PWM_PACKET_AMOUNT];

	static void init(){
		for(uint8_t i = 0; i < TEST_PWM_PACKET_AMOUNT; i++){
			test_pwm_packets[i] = new SPIPacket(TEST_PWM_1_PACKET_ID+i, TEST_PWM_PACKET_MASTER_SIZE, TEST_PWM_PACKET_SLAVE_SIZE);
		}
		spi_id = SPI::inscribe(SPI::spi3);
	}


	static void start(){
		SPI::slave_listen_packets(spi_id);
	}
};
