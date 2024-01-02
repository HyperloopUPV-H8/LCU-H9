#pragma once

#include "SPI/SPI.hpp"
#include "CommonData/CommonData.hpp"

class Communication{
public:
	uint8_t spi_id;
	SPIPacket* test_pwm_packets[TEST_PWM_PACKET_AMOUNT];

	Communication(){
		for(uint8_t i = 0; i < TEST_PWM_PACKET_AMOUNT; i++){
			test_pwm_packets[i] = new SPIPacket(TEST_PWM_1_PACKET_ID+i, 8, 0);
		}
		spi_id = SPI::inscribe(SPI::spi3);
	}

	void start(){
		SPI::slave_listen_packets(spi_id);
	}
};
