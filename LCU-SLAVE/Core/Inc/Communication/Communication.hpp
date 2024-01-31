#pragma once

#include <CommonData/CommonData.hpp>
#include <LDU/LDU.hpp>
#include "SPI/SPI.hpp"


class Communication{
public:
	static uint8_t spi_id;
	static uint16_t ldu_to_change;
	static float duty_to_change;

	SPIStackOrder* SPIOrders[ORDER_COUNT];
	SPIBasePacket* SPIPackets[ORDER_COUNT*2];

	static void init(){
		spi_id = SPI::inscribe(SPI::spi3);
	}

	Communication(){
		SPIPackets[TEST_PWM_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_to_change, &duty_to_change);
		SPIPackets[TEST_PWM_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_PWM_ORDER_INDEX] = new SPIStackOrder(TEST_PWM_PACKET_ID, *SPIPackets[TEST_PWM_ORDER_INDEX*2], *SPIPackets[TEST_PWM_ORDER_INDEX*2+1]);
		SPIOrders[TEST_PWM_ORDER_INDEX]->set_callback(test_pwm_order_callback);
	}

	static void start(){
		SPI::slave_listen_Orders(spi_id);
	}




	/* ##############################################################
	 * 				Callback functions
	 * ##############################################################
	 */

	static void test_pwm_order_callback(){
		LDU::change_ldu_duty_cycle(ldu_to_change, duty_to_change);
	}
};

