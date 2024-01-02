#pragma once

#include "SPI/SPI.hpp"
#include "Communication/Ethernet/TCP/ServerSocket.hpp"
#include "CommonData/CommonData.hpp"

class Communication{
public:
	uint8_t spi_id;
	SPIPacket* test_pwm_packets[TEST_PWM_PACKET_AMOUNT];
	ServerSocket *gui_connection;

	Communication(){
		for(uint8_t i = 0; i < TEST_PWM_PACKET_AMOUNT; i++){
			test_pwm_packets[i] = new SPIPacket(TEST_PWM_1_PACKET_ID+i, 8, 0);
		}
		spi_id = SPI::inscribe(SPI::spi3);
	}

	void start(){
		gui_connection = new ServerSocket(MASTER_IP, TCP_SERVER_PORT);
	}

	void send_pwm_data(uint8_t PWM_ID, float duty, uint32_t freq){
		SPIPacket* packet_to_send = test_pwm_packets[TEST_PWM_1_PACKET_ID + PWM_ID];


		uint8_t casted_duty_cycle_1 = (uint8_t) ( (*((uint32_t*)(&duty))) >>24);
		uint8_t casted_duty_cycle_2 = (uint8_t) ( (*((uint32_t*)(&duty))) >>16);
		uint8_t casted_duty_cycle_3 = (uint8_t) ( (*((uint32_t*)(&duty))) >>8);
		uint8_t casted_duty_cycle_4 = (uint8_t) ( (*((uint32_t*)(&duty))));
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+3] = casted_duty_cycle_1;
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+2] = casted_duty_cycle_2;
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+1] = casted_duty_cycle_3;
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE] = casted_duty_cycle_4;

		packet_to_send->master_data[TEST_PWM_PACKET_FREQ_BYTE+3] = (freq << 24);
		packet_to_send->master_data[TEST_PWM_PACKET_FREQ_BYTE+2] = (freq << 16);
		packet_to_send->master_data[TEST_PWM_PACKET_FREQ_BYTE+1] = (freq << 8);
		packet_to_send->master_data[TEST_PWM_PACKET_FREQ_BYTE] = (freq);

		SPI::master_transmit_packet(spi_id, *packet_to_send);
	}

};
