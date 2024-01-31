#pragma once

#include <CommonData/CommonData.hpp>
#include <LDU/LDU.hpp>
#include "SPI/SPI.hpp"

#define coil_t slave_control_data.fixed_coil_temperature
#define lpu_t slave_control_data.fixed_lpu_temperature
#define coil_I slave_control_data.fixed_coil_current
#define bat_V slave_control_data.fixed_battery_voltage
#define airgap slave_control_data.fixed_airgap_distance
#define ldu_array_deduction uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t
#define airgap_array_deduction uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t

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

		SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2] = new SPIPacket<41, uint8_t, ldu_array_deduction, ldu_array_deduction>(
				&slave_control_data.master_status,
				&coil_t[0], &coil_t[1], &coil_t[2], &coil_t[3], &coil_t[4], &coil_t[5], &coil_t[6], &coil_t[7], &coil_t[8], &coil_t[9],
				&lpu_t[0], &lpu_t[1], &lpu_t[2], &lpu_t[3], &lpu_t[4], &lpu_t[5], &lpu_t[6], &lpu_t[7], &lpu_t[8], &lpu_t[9]
		);
		SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2+1] = new SPIPacket<59, uint8_t, ldu_array_deduction, ldu_array_deduction, airgap_array_deduction>(
				&slave_control_data.slave_status,
				&coil_I[0], &coil_I[1], &coil_I[2], &coil_I[3], &coil_I[4], &coil_I[5], &coil_I[6], &coil_I[7], &coil_I[8], &coil_I[9],
				&bat_V[0], &bat_V[1], &bat_V[2], &bat_V[3], &bat_V[4], &bat_V[5], &bat_V[6], &bat_V[7], &bat_V[8], &bat_V[9],
				&airgap[0], &airgap[1], &airgap[2], &airgap[3], &airgap[4], &airgap[5], &airgap[6], &airgap[7]
		);
		SPIOrders[MASTER_SLAVE_DATA_ORDER_INDEX] = new SPIStackOrder(MASTER_SLAVE_DATA_ORDER_ID, *SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2], *SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2+1]);
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

