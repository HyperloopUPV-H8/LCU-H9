#pragma once

#include "ST-LIB.hpp"
#include "CommonData/CommonData.hpp"

class Communication{
public:
	static uint8_t spi_id;
	static SPIPacket* test_pwm_packets[TEST_PWM_PACKET_AMOUNT];
	static ServerSocket *gui_connection;
	static DatagramSocket *udp_connection;
	static DigitalOutput* test_order_received;
	static uint16_t pwm_to_change;
	static float duty_to_change;

	Communication():pwmOrder(TEST_PWM_TCP_PACKET_ID, send_pwm_data, &pwm_to_change, &duty_to_change){}
	HeapOrder pwmOrder;

	static void init(){
		for(uint8_t i = 0; i < TEST_PWM_PACKET_AMOUNT; i++){
			test_pwm_packets[i] = new SPIPacket(TEST_PWM_1_PACKET_ID+i, TEST_PWM_PACKET_MASTER_SIZE, TEST_PWM_PACKET_SLAVE_SIZE);
		}
		spi_id = SPI::inscribe(SPI::spi3);
	}

	static void start(){
		gui_connection = new ServerSocket(MASTER_IP, TCP_SERVER_PORT);
		udp_connection = new DatagramSocket(MASTER_IP, UDP_PORT, BACKEND, UDP_PORT);

	}

	static void send_pwm_data(){
		Communication::test_order_received->turn_on();
			Time::set_timeout(2000,[&](){
				Communication::test_order_received->turn_off();
			});
			SPIPacket* packet_to_send = test_pwm_packets[pwm_to_change];


			uint8_t casted_duty_cycle_1 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))) >>24);
			uint8_t casted_duty_cycle_2 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))) >>16);
			uint8_t casted_duty_cycle_3 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))) >>8);
			uint8_t casted_duty_cycle_4 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))));
			packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+3] = casted_duty_cycle_1;
			packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+2] = casted_duty_cycle_2;
			packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+1] = casted_duty_cycle_3;
			packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE] = casted_duty_cycle_4;

			SPI::master_transmit_packet(spi_id, *packet_to_send);
		}


	/*static void send_pwm_data(uint8_t PWM_ID, float duty){
		SPIPacket* packet_to_send = test_pwm_packets[PWM_ID];


		uint8_t casted_duty_cycle_1 = (uint8_t) ( (*((uint32_t*)(&duty))) >>24);
		uint8_t casted_duty_cycle_2 = (uint8_t) ( (*((uint32_t*)(&duty))) >>16);
		uint8_t casted_duty_cycle_3 = (uint8_t) ( (*((uint32_t*)(&duty))) >>8);
		uint8_t casted_duty_cycle_4 = (uint8_t) ( (*((uint32_t*)(&duty))));
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+3] = casted_duty_cycle_1;
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+2] = casted_duty_cycle_2;
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE+1] = casted_duty_cycle_3;
		packet_to_send->master_data[TEST_PWM_PACKET_DUTY_BYTE] = casted_duty_cycle_4;

		SPI::master_transmit_packet(spi_id, *packet_to_send);
	}*/

};
