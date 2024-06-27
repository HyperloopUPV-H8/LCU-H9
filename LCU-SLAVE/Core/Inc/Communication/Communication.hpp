#pragma once

#include <CommonData/CommonData.hpp>
#include "SPI/SPI.hpp"

#define coil_t shared_control_data.fixed_coil_temperature
#define lpu_t shared_control_data.fixed_lpu_temperature
#define coil_I shared_control_data.fixed_coil_current
#define bat_V shared_control_data.fixed_battery_voltage
#define airgap shared_control_data.fixed_airgap_distance
#define ldu_array_deduction uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t
#define float_ldu_array_deduction float, float, float, float, float, float, float, float, float, float
#define airgap_array_deduction uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t


class Communication{
public:
	static uint8_t spi_id;

	SPIStackOrder* SPIOrders[SPI_ORDER_COUNT];
	SPIBasePacket* SPIPackets[SPI_ORDER_COUNT*2];

	static struct communication_flags{
		bool SPIEstablished = false;
	}flags;

	static void init(){
		spi_id = SPI::inscribe(SPI::spi3);
		SPI::assign_RS(spi_id, SPI_RS_PIN);
	}

	Communication(){
	}

	void define_packets(){
		define_shared_data();

		SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2] = new SPIPacket<2, uint8_t, uint8_t>(shared_control_data.master_status, shared_control_data.master_running_mode);
		SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2+1] = new SPIPacket<43, uint8_t, uint8_t, uint8_t, float_ldu_array_deduction>(
				shared_control_data.slave_status, shared_control_data.slave_running_mode, shared_control_data.slave_secondary_status,
				shared_control_data.shunt_zeroing_offset[0],shared_control_data.shunt_zeroing_offset[1],shared_control_data.shunt_zeroing_offset[2],
				shared_control_data.shunt_zeroing_offset[3],shared_control_data.shunt_zeroing_offset[4],shared_control_data.shunt_zeroing_offset[5],
				shared_control_data.shunt_zeroing_offset[6],shared_control_data.shunt_zeroing_offset[7],shared_control_data.shunt_zeroing_offset[8],
				shared_control_data.shunt_zeroing_offset[9]);
		SPIOrders[MASTER_SLAVE_INITIAL_ORDER_INDEX] = new SPIStackOrder(MASTER_SLAVE_INITIAL_ORDER_ID, *SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2], *SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2+1]);
		SPIOrders[MASTER_SLAVE_INITIAL_ORDER_INDEX]->set_callback(initial_order_callback);


		SPIPackets[SENSOR_DATA_ORDER_INDEX*2] = new SPIPacket<42, uint8_t, uint8_t, ldu_array_deduction, ldu_array_deduction>(
			shared_control_data.master_status, shared_control_data.master_secondary_status,
			&coil_t[0], &coil_t[1], &coil_t[2], &coil_t[3], &coil_t[4], &coil_t[5], &coil_t[6], &coil_t[7], &coil_t[8], &coil_t[9],
			&lpu_t[0], &lpu_t[1], &lpu_t[2], &lpu_t[3], &lpu_t[4], &lpu_t[5], &lpu_t[6], &lpu_t[7], &lpu_t[8], &lpu_t[9]
		);
		SPIPackets[SENSOR_DATA_ORDER_INDEX*2+1] = new SPIPacket<60, uint8_t, uint8_t, ldu_array_deduction, ldu_array_deduction, airgap_array_deduction>(
			shared_control_data.slave_status, shared_control_data.slave_secondary_status,
			coil_I[0], coil_I[1], coil_I[2], coil_I[3], coil_I[4], coil_I[5], coil_I[6], coil_I[7], coil_I[8], coil_I[9],
			bat_V[0], bat_V[1], bat_V[2], bat_V[3], bat_V[4], bat_V[5], bat_V[6], bat_V[7], bat_V[8], bat_V[9],
			airgap[0], airgap[1], airgap[2], airgap[3], airgap[4], airgap[5], airgap[6], airgap[7]
		);
		SPIOrders[SENSOR_DATA_ORDER_INDEX] = new SPIStackOrder(SENSOR_DATA_ORDER_ID, *SPIPackets[SENSOR_DATA_ORDER_INDEX*2], *SPIPackets[SENSOR_DATA_ORDER_INDEX*2+1]);


		SPIPackets[LEVITATION_DATA_ORDER_INDEX*2] = new SPIPacket<0>();
		SPIPackets[LEVITATION_DATA_ORDER_INDEX*2+1] = new SPIPacket<100, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float>(
			shared_control_data.float_current_ref[0], shared_control_data.float_current_ref[1], shared_control_data.float_current_ref[2], shared_control_data.float_current_ref[3], shared_control_data.float_current_ref[4],
			shared_control_data.float_current_ref[5], shared_control_data.float_current_ref[6], shared_control_data.float_current_ref[7], shared_control_data.float_current_ref[8], shared_control_data.float_current_ref[9],
			shared_control_data.float_airgap_to_pos[0], shared_control_data.float_airgap_to_pos[1], shared_control_data.float_airgap_to_pos[2], shared_control_data.float_airgap_to_pos[3],shared_control_data.float_airgap_to_pos[4],
			shared_control_data.float_airgap_to_pos_der[0],shared_control_data.float_airgap_to_pos_der[1], shared_control_data.float_airgap_to_pos_der[2], shared_control_data.float_airgap_to_pos_der[3],shared_control_data.float_airgap_to_pos_der[4],
			shared_control_data.float_airgap_to_pos_in[0], shared_control_data.float_airgap_to_pos_in[1], shared_control_data.float_airgap_to_pos_in[2], shared_control_data.float_airgap_to_pos_in[3], shared_control_data.float_airgap_to_pos_in[4]
		);
		SPIOrders[LEVITATION_DATA_ORDER_INDEX] = new SPIStackOrder(LEVITATION_DATA_ORDER_ID, *SPIPackets[LEVITATION_DATA_ORDER_INDEX*2], *SPIPackets[LEVITATION_DATA_ORDER_INDEX*2+1]);


		SPIPackets[TEST_PWM_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_to_change, &duty_to_change);
		SPIPackets[TEST_PWM_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_PWM_ORDER_INDEX] = new SPIStackOrder(TEST_PWM_ORDER_ID, *SPIPackets[TEST_PWM_ORDER_INDEX*2], *SPIPackets[TEST_PWM_ORDER_INDEX*2+1]);
		SPIOrders[TEST_PWM_ORDER_INDEX]->set_callback(test_pwm_order_callback);


		SPIPackets[TEST_VBAT_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_to_change, &data_to_change);
		SPIPackets[TEST_VBAT_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_VBAT_ORDER_INDEX] = new SPIStackOrder(TEST_VBAT_ORDER_ID, *SPIPackets[TEST_VBAT_ORDER_INDEX*2], *SPIPackets[TEST_VBAT_ORDER_INDEX*2+1]);
		SPIOrders[TEST_VBAT_ORDER_INDEX]->set_callback(start_levitation_control);


		SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2] = new SPIPacket<4,float>(&data_to_change);
		SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[START_LEVITATION_CONTROL_ORDER_INDEX] = new SPIStackOrder(START_LEVITATION_CONTROL_ORDER_ID, *SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2], *SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2+1]);
		SPIOrders[START_LEVITATION_CONTROL_ORDER_INDEX]->set_callback(start_levitation_control);


		SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_to_change, &data_to_change);
		SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_DESIRED_CURRENT_ORDER_INDEX] = new SPIStackOrder(TEST_DESIRED_CURRENT_ORDER_ID, *SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2], *SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2+1]);
		SPIOrders[TEST_DESIRED_CURRENT_ORDER_INDEX]->set_callback(set_desired_current_on_LDU);


		SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2] = new SPIPacket<4,float>(&data_to_change);
		SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[START_VERTICAL_LEVITATION_ORDER_INDEX] = new SPIStackOrder(START_VERTICAL_LEVITATION_ORDER_ID, *SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2], *SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2+1]);
		SPIOrders[START_VERTICAL_LEVITATION_ORDER_INDEX]->set_callback(start_vertical_levitation);


		SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2] = new SPIPacket<0>;
		SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[START_HORIZONTAL_LEVITATION_ORDER_INDEX] = new SPIStackOrder(START_HORIZONTAL_LEVITATION_ORDER_ID, *SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2], *SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2+1]);
		SPIOrders[START_HORIZONTAL_LEVITATION_ORDER_INDEX]->set_callback(start_horizontal_levitation);


		SPIPackets[STOP_LEVITATION_ORDER_INDEX*2] = new SPIPacket<0>;
		SPIPackets[STOP_LEVITATION_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[STOP_LEVITATION_ORDER_INDEX] = new SPIStackOrder(STOP_LEVITATION_ORDER_ID, *SPIPackets[STOP_LEVITATION_ORDER_INDEX*2], *SPIPackets[STOP_LEVITATION_ORDER_INDEX*2+1]);
		SPIOrders[STOP_LEVITATION_ORDER_INDEX]->set_callback(shutdown);

		SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2] = new SPIPacket<0>();
		SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2+1] = new SPIPacket<50,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t>(
	  &airgaps_samples[0],&airgaps_samples[1],&airgaps_samples[2],&airgaps_samples[3],&airgaps_samples[4],&airgaps_samples[5],&airgaps_samples[6],&airgaps_samples[7],&airgaps_samples[8],&airgaps_samples[9],
	  &airgaps_samples[10],&airgaps_samples[11],&airgaps_samples[12],&airgaps_samples[13],&airgaps_samples[14],&airgaps_samples[15],&airgaps_samples[16],&airgaps_samples[17],&airgaps_samples[18],&airgaps_samples[19],
	  &airgaps_samples[20],&airgaps_samples[21],&airgaps_samples[22],&airgaps_samples[23],&airgaps_samples[24],&airgaps_samples[25],&airgaps_samples[26],&airgaps_samples[27],&airgaps_samples[28],&airgaps_samples[29],
	  &airgaps_samples[30],&airgaps_samples[31],&airgaps_samples[32],&airgaps_samples[33],&airgaps_samples[34],&airgaps_samples[35],&airgaps_samples[36],&airgaps_samples[37],&airgaps_samples[38],&airgaps_samples[39],
	  &airgaps_samples[40],&airgaps_samples[41],&airgaps_samples[42],&airgaps_samples[43],&airgaps_samples[44],&airgaps_samples[45],&airgaps_samples[46],&airgaps_samples[47],&airgaps_samples[48],&airgaps_samples[49]);
		SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2] = new SPIPacket<0>();
		SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2+1] = new SPIPacket<50,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t>(
	  &airgaps_samples[50],&airgaps_samples[51],&airgaps_samples[52],&airgaps_samples[53],&airgaps_samples[54],&airgaps_samples[55],&airgaps_samples[56],&airgaps_samples[57],&airgaps_samples[58],&airgaps_samples[59],
	  &airgaps_samples[60],&airgaps_samples[61],&airgaps_samples[62],&airgaps_samples[63],&airgaps_samples[64],&airgaps_samples[65],&airgaps_samples[66],&airgaps_samples[67],&airgaps_samples[68],&airgaps_samples[69],
	  &airgaps_samples[70],&airgaps_samples[71],&airgaps_samples[72],&airgaps_samples[73],&airgaps_samples[74],&airgaps_samples[75],&airgaps_samples[76],&airgaps_samples[77],&airgaps_samples[78],&airgaps_samples[79],
	  &airgaps_samples[80],&airgaps_samples[81],&airgaps_samples[82],&airgaps_samples[83],&airgaps_samples[84],&airgaps_samples[85],&airgaps_samples[86],&airgaps_samples[87],&airgaps_samples[88],&airgaps_samples[89],
	  &airgaps_samples[90],&airgaps_samples[91],&airgaps_samples[92],&airgaps_samples[93],&airgaps_samples[94],&airgaps_samples[95],&airgaps_samples[96],&airgaps_samples[97],&airgaps_samples[98],&airgaps_samples[99]
										 );
		SPIOrders[AIRGAPS_PACKET_ORDER_INDEX] = new SPIStackOrder(AIRGAPS_PACKET, *SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2], *SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2+1]);
		SPIOrders[AIRGAPS_PACKET_2_ORDER_INDEX] = new SPIStackOrder(AIRGAPS_PACKET_2, *SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2], *SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2+1]);
	}

	static void start(){
		SPI::slave_listen_Orders(spi_id);
	}

	static void update(){
		SPI::Order_update();
	}
};

