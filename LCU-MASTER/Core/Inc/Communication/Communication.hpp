#pragma once

#include "ST-LIB.hpp"
#include "CommonData/CommonData.hpp"

class Communication{
public:
	static uint8_t spi_id;
	static ServerSocket *gui_connection;
	static DatagramSocket *udp_connection;
	static DigitalOutput* test_order_received;
	static uint16_t ldu_to_change;
	static float duty_to_change;
	HeapOrder pwmOrder;

	SPIStackOrder* SPIOrders[SPI_ORDER_COUNT];
	SPIBasePacket* SPIPackets[SPI_ORDER_COUNT*2];

	static void init(){
		spi_id = SPI::inscribe(SPI::spi3);
	}

	Communication():pwmOrder(TEST_PWM_TCP_PACKET_ID, send_pwm_data, &ldu_to_change, &duty_to_change){
		SPIPackets[TEST_PWM_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_to_change, &duty_to_change);
		SPIPackets[TEST_PWM_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_PWM_ORDER_INDEX] = new SPIStackOrder(TEST_PWM_PACKET_ID, *SPIPackets[TEST_PWM_ORDER_INDEX*2], *SPIPackets[TEST_PWM_ORDER_INDEX*2+1]);
	}


	static void start(){
		gui_connection = new ServerSocket(MASTER_IP, TCP_SERVER_PORT);
		udp_connection = new DatagramSocket(MASTER_IP, UDP_PORT, BACKEND, UDP_PORT);
	}

	static void send_pwm_data(){
		Communication::test_order_received->turn_on();
		Time::set_timeout(500,[&](){
			Communication::test_order_received->turn_off();
		});

		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[TEST_PWM_PACKET_ID]);
	}


	/*static void send_pwm_data(){
		Communication::test_order_received->turn_on();
		Time::set_timeout(500,[&](){
			Communication::test_order_received->turn_off();
		});
		SPI_processing_packet = SPIPacket::SPIPacketsByID[pwm_to_change+TEST_PWM_1_PACKET_ID];

		uint8_t casted_duty_cycle_1 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))) >>24);
		uint8_t casted_duty_cycle_2 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))) >>16);
		uint8_t casted_duty_cycle_3 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))) >>8);
		uint8_t casted_duty_cycle_4 = (uint8_t) ( (*((uint32_t*)(&duty_to_change))));
		SPI_processing_packet->master_data[TEST_PWM_PACKET_DUTY_BYTE+3] = casted_duty_cycle_1;
		SPI_processing_packet->master_data[TEST_PWM_PACKET_DUTY_BYTE+2] = casted_duty_cycle_2;
		SPI_processing_packet->master_data[TEST_PWM_PACKET_DUTY_BYTE+1] = casted_duty_cycle_3;
		SPI_processing_packet->master_data[TEST_PWM_PACKET_DUTY_BYTE] = casted_duty_cycle_4;
		SPI::master_transmit_packet(spi_id, *SPI_processing_packet);
	}*/

};
