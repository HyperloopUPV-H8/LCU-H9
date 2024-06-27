#pragma once

#include "ST-LIB.hpp"
#include "CommonData/CommonData.hpp"

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
	static ServerSocket *gui_connection; //TODO: remove this for good
	static ServerSocket *vcu_connection;
	static DatagramSocket *upd_gui;
	static DatagramSocket *udp_vcu;
	static DigitalOutput* test_order_received;

	static Order* EthernetOrders[ETH_ORDER_COUNT];
	static Packet* EthernetPackets[ETH_PACKET_COUNT];
	SPIStackOrder* SPIOrders[SPI_ORDER_COUNT];
	SPIBasePacket* SPIPackets[SPI_ORDER_COUNT*2];


	static struct communication_flags{
		bool SPIEstablished = false;
	}flags;


	static uint16_t ldu_number_to_change;
	static uint16_t ldu_index_to_change;
	static float duty_to_change;
	static float data_from_backend;
	static float data_to_change;
	static bool new_slave_data;

	static void init(){
		spi_id = SPI::inscribe(SPI::spi3);
		SPI::assign_RS(spi_id, SPI_RS_PIN);
	}

	Communication(){
	}

	static void start(){
		start_ethernet();
	}

	static void start_ethernet(){
		gui_connection = new ServerSocket(LCU_IP, TCP_SERVER_PORT);
		vcu_connection = new ServerSocket(LCU_IP, TCP_VCU_PORT);
		upd_gui = new DatagramSocket(LCU_IP, UDP_PORT, BACKEND, UDP_PORT);
		udp_vcu = new DatagramSocket(LCU_IP, UDP_VCU_PORT, VCU_IP, UDP_VCU_PORT);

		//PACKETS
		EthernetPackets[SEND_LEVITATION_DATA_TCP_PACKET_INDEX] = new StackPacket(SEND_LEVITATION_DATA_TCP_PACKET_ID,
			shared_control_data.current_control_count, shared_control_data.levitation_control_count,
			shared_control_data.float_current_ref[0], shared_control_data.float_current_ref[1], shared_control_data.float_current_ref[2],
			shared_control_data.float_current_ref[3], shared_control_data.float_current_ref[4],
			shared_control_data.float_current_ref[5],
			shared_control_data.float_current_ref[6], shared_control_data.float_current_ref[7], shared_control_data.float_current_ref[8],
			shared_control_data.float_current_ref[9],
			shared_control_data.float_airgap_to_pos[0], shared_control_data.float_airgap_to_pos_der[0], shared_control_data.float_airgap_to_pos_in[0],
			shared_control_data.float_airgap_to_pos[1], shared_control_data.float_airgap_to_pos_der[1], shared_control_data.float_airgap_to_pos_in[1],
			shared_control_data.float_airgap_to_pos[2], shared_control_data.float_airgap_to_pos_der[2], shared_control_data.float_airgap_to_pos_in[2],
			shared_control_data.float_airgap_to_pos[3], shared_control_data.float_airgap_to_pos_der[3], shared_control_data.float_airgap_to_pos_in[3],
			shared_control_data.float_airgap_to_pos[4], shared_control_data.float_airgap_to_pos_der[4], shared_control_data.float_airgap_to_pos_in[4]
		);

		EthernetPackets[AIRGAPS_FULL_DATA_TCP_INDEX] = new StackPacket(AIRGAPS_FULL_DATA_TCP_ID,
				&airgaps_data.buffer[0],&airgaps_data.buffer[1],&airgaps_data.buffer[2],&airgaps_data.buffer[3],&airgaps_data.buffer[4],&airgaps_data.buffer[5],&airgaps_data.buffer[6],&airgaps_data.buffer[7],&airgaps_data.buffer[8],&airgaps_data.buffer[9],
				&airgaps_data.buffer[10],&airgaps_data.buffer[11],&airgaps_data.buffer[12],&airgaps_data.buffer[13],&airgaps_data.buffer[14],&airgaps_data.buffer[15],&airgaps_data.buffer[16],&airgaps_data.buffer[17],&airgaps_data.buffer[18],&airgaps_data.buffer[19],
				&airgaps_data.buffer[20],&airgaps_data.buffer[21],&airgaps_data.buffer[22],&airgaps_data.buffer[23],&airgaps_data.buffer[24],&airgaps_data.buffer[25],&airgaps_data.buffer[26],&airgaps_data.buffer[27],&airgaps_data.buffer[28],&airgaps_data.buffer[29],
				&airgaps_data.buffer[30],&airgaps_data.buffer[31],&airgaps_data.buffer[32],&airgaps_data.buffer[33],&airgaps_data.buffer[34],&airgaps_data.buffer[35],&airgaps_data.buffer[36],&airgaps_data.buffer[37],&airgaps_data.buffer[38],&airgaps_data.buffer[39],
				&airgaps_data.buffer[40],&airgaps_data.buffer[41],&airgaps_data.buffer[42],&airgaps_data.buffer[43],&airgaps_data.buffer[44],&airgaps_data.buffer[45],&airgaps_data.buffer[46],&airgaps_data.buffer[47],&airgaps_data.buffer[48],&airgaps_data.buffer[49],
				&airgaps_data.buffer[50],&airgaps_data.buffer[51],&airgaps_data.buffer[52],&airgaps_data.buffer[53],&airgaps_data.buffer[54],&airgaps_data.buffer[55],&airgaps_data.buffer[56],&airgaps_data.buffer[57],&airgaps_data.buffer[58],&airgaps_data.buffer[59],
				&airgaps_data.buffer[60],&airgaps_data.buffer[61],&airgaps_data.buffer[62],&airgaps_data.buffer[63],&airgaps_data.buffer[64],&airgaps_data.buffer[65],&airgaps_data.buffer[66],&airgaps_data.buffer[67],&airgaps_data.buffer[68],&airgaps_data.buffer[69],
				&airgaps_data.buffer[70],&airgaps_data.buffer[71],&airgaps_data.buffer[72],&airgaps_data.buffer[73],&airgaps_data.buffer[74],&airgaps_data.buffer[75],&airgaps_data.buffer[76],&airgaps_data.buffer[77],&airgaps_data.buffer[78],&airgaps_data.buffer[79],
				&airgaps_data.buffer[80],&airgaps_data.buffer[81],&airgaps_data.buffer[82],&airgaps_data.buffer[83],&airgaps_data.buffer[84],&airgaps_data.buffer[85],&airgaps_data.buffer[86],&airgaps_data.buffer[87],&airgaps_data.buffer[88],&airgaps_data.buffer[89],
				&airgaps_data.buffer[90],&airgaps_data.buffer[91],&airgaps_data.buffer[92],&airgaps_data.buffer[93],&airgaps_data.buffer[94],&airgaps_data.buffer[95],&airgaps_data.buffer[96],&airgaps_data.buffer[97],&airgaps_data.buffer[98],&airgaps_data.buffer[99]
		);

		EthernetPackets[SEND_LCU_DATA_TCP_PACKET_INDEX] = new StackPacket(SEND_LCU_DATA_TCP_PACKET_ID,
			shared_control_data.master_status, shared_control_data.slave_status,
			&shared_control_data.float_coil_temperature[0],&shared_control_data.float_coil_temperature[1],&shared_control_data.float_coil_temperature[2],
			&shared_control_data.float_coil_temperature[3],&shared_control_data.float_coil_temperature[4],&shared_control_data.float_coil_temperature[5],
			&shared_control_data.float_coil_temperature[6],&shared_control_data.float_coil_temperature[7],&shared_control_data.float_coil_temperature[8],
			&shared_control_data.float_coil_temperature[9],
			&shared_control_data.float_lpu_temperature[0],&shared_control_data.float_lpu_temperature[1],&shared_control_data.float_lpu_temperature[2],
			&shared_control_data.float_lpu_temperature[3],&shared_control_data.float_lpu_temperature[4],&shared_control_data.float_lpu_temperature[5],
			&shared_control_data.float_lpu_temperature[6],&shared_control_data.float_lpu_temperature[7],&shared_control_data.float_lpu_temperature[8],
			&shared_control_data.float_lpu_temperature[9],
			shared_control_data.float_coil_current[0],shared_control_data.float_coil_current[1],shared_control_data.float_coil_current[2],
			shared_control_data.float_coil_current[3],shared_control_data.float_coil_current[4],shared_control_data.float_coil_current[5],
			shared_control_data.float_coil_current[6],shared_control_data.float_coil_current[7],shared_control_data.float_coil_current[8],
			shared_control_data.float_coil_current[9],
			shared_control_data.float_battery_voltage[0],shared_control_data.float_battery_voltage[1],shared_control_data.float_battery_voltage[2],
			shared_control_data.float_battery_voltage[3],shared_control_data.float_battery_voltage[4],shared_control_data.float_battery_voltage[5],
			shared_control_data.float_battery_voltage[6],shared_control_data.float_battery_voltage[7],shared_control_data.float_battery_voltage[8],
			shared_control_data.float_battery_voltage[9],
			shared_control_data.float_airgap_distance[0],shared_control_data.float_airgap_distance[1],shared_control_data.float_airgap_distance[2],
			shared_control_data.float_airgap_distance[3],shared_control_data.float_airgap_distance[4],shared_control_data.float_airgap_distance[5],
			shared_control_data.float_airgap_distance[6],shared_control_data.float_airgap_distance[7]
		);

		EthernetPackets[LPU_VOLTAGE_INTEGER_DATA_TCP_PACKET_INDEX] = new StackPacket(LPU_VOLTAGE_INTEGER_DATA_TCP_PACKET_ID, &shared_pod_data.average_integer_lpu_voltage);

		//ORDERS
		for(int i = 0; i < 2; i++){
		EthernetOrders[TEST_PWM_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<6,uint16_t,float>(TEST_PWM_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), send_pwm_data_from_backend, &ldu_number_to_change, &duty_to_change);
		EthernetOrders[START_LEVITATION_CONTROL_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<4,float>(START_LEVITATION_CONTROL_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), start_slave_levitation_control, &data_from_backend);
		EthernetOrders[TEST_DESIRED_CURRENT_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<6,uint16_t,float>(TEST_DESIRED_CURRENT_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), send_desired_current_data_from_backend, &ldu_number_to_change, &data_from_backend);
		EthernetOrders[TEST_START_RESET_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<2,uint16_t>(TEST_START_RESET_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), fix_buffer_reset_high, &ldu_number_to_change);
		EthernetOrders[TEST_STOP_RESET_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<2,uint16_t>(TEST_STOP_RESET_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), fix_buffer_reset_low, &ldu_number_to_change);

		EthernetOrders[START_VERTICAL_LEVITATION_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<4,float>(START_VERTICAL_LEVITATION_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), start_slave_vertical_levitation, &data_from_backend);
		EthernetOrders[STOP_LEVITATION_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<0>(STOP_LEVITATION_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), stop_slave_levitation);
		EthernetOrders[STICK_DOWN_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<0>(STICK_DOWN_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), stick_down_slave);
		EthernetOrders[LANDING_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<0>(LANDING_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), landing_slave);
		EthernetOrders[START_HORIZONTAL_LEVITATION_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<0>(START_HORIZONTAL_LEVITATION_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), start_slave_horizontal_levitation);

		EthernetOrders[STABLE_LEVITATION_CONFIRMATION_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<0>(STABLE_LEVITATION_CONFIRMATION_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), nullptr);
		EthernetOrders[LANDING_COMPLETE_CONFIRMATION_TCP_ORDER_INDEX+(i*ETH_ORDER_BYPASS_INDEX_TO_ADD)] = new StackOrder<0>(LANDING_COMPLETE_CONFIRMATION_TCP_ORDER_ID+(i*ETH_ORDER_BYPASS_ID_TO_ADD), nullptr);
		}
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


		SPIPackets[TEST_PWM_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_index_to_change, &duty_to_change);
		SPIPackets[TEST_PWM_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_PWM_ORDER_INDEX] = new SPIStackOrder(TEST_PWM_ORDER_ID, *SPIPackets[TEST_PWM_ORDER_INDEX*2], *SPIPackets[TEST_PWM_ORDER_INDEX*2+1]);


		SPIPackets[TEST_VBAT_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_index_to_change, &data_to_change);
		SPIPackets[TEST_VBAT_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_VBAT_ORDER_INDEX] = new SPIStackOrder(TEST_VBAT_ORDER_ID, *SPIPackets[TEST_VBAT_ORDER_INDEX*2], *SPIPackets[TEST_VBAT_ORDER_INDEX*2+1]);


		SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2] = new SPIPacket<4,float>(&data_to_change);
		SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[START_LEVITATION_CONTROL_ORDER_INDEX] = new SPIStackOrder(START_LEVITATION_CONTROL_ORDER_ID, *SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2], *SPIPackets[START_LEVITATION_CONTROL_ORDER_INDEX*2+1]);


		SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2] = new SPIPacket<6,uint16_t,float>(&ldu_index_to_change, &data_to_change);
		SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[TEST_DESIRED_CURRENT_ORDER_INDEX] = new SPIStackOrder(TEST_DESIRED_CURRENT_ORDER_ID, *SPIPackets[TEST_DESIRED_CURRENT_ORDER_INDEX*2], *SPIPackets[TEST_VBAT_ORDER_INDEX*2+1]);


		SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2] = new SPIPacket<4,float>(&data_to_change);
		SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[START_VERTICAL_LEVITATION_ORDER_INDEX] = new SPIStackOrder(START_VERTICAL_LEVITATION_ORDER_ID, *SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2], *SPIPackets[START_VERTICAL_LEVITATION_ORDER_INDEX*2+1]);


		SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2] = new SPIPacket<0>;
		SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[START_HORIZONTAL_LEVITATION_ORDER_INDEX] = new SPIStackOrder(START_HORIZONTAL_LEVITATION_ORDER_ID, *SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2], *SPIPackets[START_HORIZONTAL_LEVITATION_ORDER_INDEX*2+1]);


		SPIPackets[STOP_LEVITATION_ORDER_INDEX*2] = new SPIPacket<0>;
		SPIPackets[STOP_LEVITATION_ORDER_INDEX*2+1] = new SPIPacket<0>;
		SPIOrders[STOP_LEVITATION_ORDER_INDEX] = new SPIStackOrder(STOP_LEVITATION_ORDER_ID, *SPIPackets[STOP_LEVITATION_ORDER_INDEX*2], *SPIPackets[STOP_LEVITATION_ORDER_INDEX*2+1]);


		SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2] = new SPIPacket<0>();
		SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2+1] = new SPIPacket<100,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t>(
	  &airgaps_samples.buffer[0],&airgaps_samples.buffer[1],&airgaps_samples.buffer[2],&airgaps_samples.buffer[3],&airgaps_samples.buffer[4],&airgaps_samples.buffer[5],&airgaps_samples.buffer[6],&airgaps_samples.buffer[7],&airgaps_samples.buffer[8],&airgaps_samples.buffer[9],
	  &airgaps_samples.buffer[10],&airgaps_samples.buffer[11],&airgaps_samples.buffer[12],&airgaps_samples.buffer[13],&airgaps_samples.buffer[14],&airgaps_samples.buffer[15],&airgaps_samples.buffer[16],&airgaps_samples.buffer[17],&airgaps_samples.buffer[18],&airgaps_samples.buffer[19],
	  &airgaps_samples.buffer[20],&airgaps_samples.buffer[21],&airgaps_samples.buffer[22],&airgaps_samples.buffer[23],&airgaps_samples.buffer[24],&airgaps_samples.buffer[25],&airgaps_samples.buffer[26],&airgaps_samples.buffer[27],&airgaps_samples.buffer[28],&airgaps_samples.buffer[29],
	  &airgaps_samples.buffer[30],&airgaps_samples.buffer[31],&airgaps_samples.buffer[32],&airgaps_samples.buffer[33],&airgaps_samples.buffer[34],&airgaps_samples.buffer[35],&airgaps_samples.buffer[36],&airgaps_samples.buffer[37],&airgaps_samples.buffer[38],&airgaps_samples.buffer[39],
	  &airgaps_samples.buffer[40],&airgaps_samples.buffer[41],&airgaps_samples.buffer[42],&airgaps_samples.buffer[43],&airgaps_samples.buffer[44],&airgaps_samples.buffer[45],&airgaps_samples.buffer[46],&airgaps_samples.buffer[47],&airgaps_samples.buffer[48],&airgaps_samples.buffer[49]);
		SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2] = new SPIPacket<0>();
		SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2+1] = new SPIPacket<100,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,
										 uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t>(
	  &airgaps_samples.buffer[50],&airgaps_samples.buffer[51],&airgaps_samples.buffer[52],&airgaps_samples.buffer[53],&airgaps_samples.buffer[54],&airgaps_samples.buffer[55],&airgaps_samples.buffer[56],&airgaps_samples.buffer[57],&airgaps_samples.buffer[58],&airgaps_samples.buffer[59],
	  &airgaps_samples.buffer[60],&airgaps_samples.buffer[61],&airgaps_samples.buffer[62],&airgaps_samples.buffer[63],&airgaps_samples.buffer[64],&airgaps_samples.buffer[65],&airgaps_samples.buffer[66],&airgaps_samples.buffer[67],&airgaps_samples.buffer[68],&airgaps_samples.buffer[69],
	  &airgaps_samples.buffer[70],&airgaps_samples.buffer[71],&airgaps_samples.buffer[72],&airgaps_samples.buffer[73],&airgaps_samples.buffer[74],&airgaps_samples.buffer[75],&airgaps_samples.buffer[76],&airgaps_samples.buffer[77],&airgaps_samples.buffer[78],&airgaps_samples.buffer[79],
	  &airgaps_samples.buffer[80],&airgaps_samples.buffer[81],&airgaps_samples.buffer[82],&airgaps_samples.buffer[83],&airgaps_samples.buffer[84],&airgaps_samples.buffer[85],&airgaps_samples.buffer[86],&airgaps_samples.buffer[87],&airgaps_samples.buffer[88],&airgaps_samples.buffer[89],
	  &airgaps_samples.buffer[90],&airgaps_samples.buffer[91],&airgaps_samples.buffer[92],&airgaps_samples.buffer[93],&airgaps_samples.buffer[94],&airgaps_samples.buffer[95],&airgaps_samples.buffer[96],&airgaps_samples.buffer[97],&airgaps_samples.buffer[98],&airgaps_samples.buffer[99]
										 );
		SPIOrders[AIRGAPS_PACKET_ORDER_INDEX] = new SPIStackOrder(AIRGAPS_PACKET, *SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2], *SPIPackets[AIRGAPS_PACKET_ORDER_INDEX*2+1]);
		SPIOrders[AIRGAPS_PACKET_2_ORDER_INDEX] = new SPIStackOrder(AIRGAPS_PACKET_2, *SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2], *SPIPackets[AIRGAPS_PACKET_2_ORDER_INDEX*2+1]);

		SPIOrders[AIRGAPS_PACKET_ORDER_INDEX]->set_callback(parse_first_half_airgaps);
		SPIOrders[AIRGAPS_PACKET_2_ORDER_INDEX]->set_callback(parse_second_half_airgaps);
	}


	static void update(){
if constexpr(USING_1DOF){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			*shared_control_data.float_airgap_distance[i] = DOF1_airgap_distance_binary_to_float(*shared_control_data.fixed_airgap_distance[i])*1000;
		}
		for(int i = 0; i < LDU_COUNT; i++){
			*shared_control_data.float_coil_current[i] = coil_current_binary_to_real(i,*shared_control_data.fixed_coil_current[i]);
			*shared_control_data.float_battery_voltage[i] = battery_voltage_binary_to_real(*shared_control_data.fixed_battery_voltage[i]);
		}
}
if constexpr(USING_5DOF){
		shared_pod_data.average_integer_lpu_voltage = 0;
		for(int i = 0; i < AIRGAP_COUNT; i++){
			*shared_control_data.float_airgap_distance[i] = airgap_distance_binary_to_float(i, *shared_control_data.fixed_airgap_distance[i])*1000;
		}
		for(int i = 0; i < LDU_COUNT; i++){
			*shared_control_data.float_coil_current[i] = coil_current_binary_to_real(i,*shared_control_data.fixed_coil_current[i]) - *shared_control_data.shunt_zeroing_offset[i];
			*shared_control_data.float_battery_voltage[i] = battery_voltage_binary_to_real(*shared_control_data.fixed_battery_voltage[i]);
			shared_pod_data.integer_lpu_voltage[i] = battery_voltage_binary_to_OBCCU(*shared_control_data.fixed_battery_voltage[i]);
			shared_pod_data.average_integer_lpu_voltage += shared_pod_data.integer_lpu_voltage[i];
		}
		shared_pod_data.average_integer_lpu_voltage /= LDU_COUNT;
}
	}

	//###################  PERIODIC FUNCTIONS  #########################

	static void send_lcu_data_to_backend(){
		upd_gui->send_packet(*EthernetPackets[SEND_LCU_DATA_TCP_PACKET_INDEX]);
	}

	static void send_levitation_data_to_backend(){
		upd_gui->send_packet(*EthernetPackets[SEND_LEVITATION_DATA_TCP_PACKET_INDEX]);
	}

	static void send_voltage_data_to_OBCCU(){
		udp_vcu->send_packet(*EthernetPackets[LPU_VOLTAGE_INTEGER_DATA_TCP_PACKET_INDEX]);
	}

	static void lcu_data_transaction(){
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[SENSOR_DATA_ORDER_ID]);
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[LEVITATION_DATA_ORDER_ID]);
	}

	static void lcu_initial_transaction(){
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[MASTER_SLAVE_INITIAL_ORDER_ID]);
	}

	//#####################  SPI ORDERS CALLBACKS #######################

	static inline float coil_current_calculation(uint16_t coil_current){
		return coil_current / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}

	static inline float battery_voltage_calculation(uint16_t battery_voltage){
		return battery_voltage / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}

	static inline float airgap_distance_calculation(uint16_t airgap_distance){
		return airgap_distance / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}

	static inline void parse_first_half_airgaps(){
		for(int i = 0; i < 50; i++){
			airgaps_data.buffer[i] = airgap_distance_binary_to_float(0,airgaps_samples.buffer[i]);
		}
	}

	static inline void parse_second_half_airgaps(){
		for(int i = 50; i < 100; i++){
			airgaps_data.buffer[i] = airgap_distance_binary_to_float(0,airgaps_samples.buffer[i]);
		}
	}
	//################# ETH TESTING ORDERS CALLBACKS ####################

	static void send_pwm_data_from_backend(){
		ldu_index_to_change = ldu_number_to_change - 1;
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[TEST_PWM_ORDER_ID]);
	}

	static void send_vbat_data_from_backend(){
		ldu_index_to_change = ldu_number_to_change - 1;
		data_to_change = (float) data_from_backend;
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[TEST_VBAT_ORDER_ID]);
	}

	static void start_slave_levitation_control(){
		data_to_change = (float) data_from_backend;
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[START_LEVITATION_CONTROL_ORDER_ID]);
	}

	static void send_desired_current_data_from_backend(){
		ldu_index_to_change = ldu_number_to_change - 1;
		data_to_change = (float) data_from_backend;
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[TEST_DESIRED_CURRENT_ORDER_ID]);
	}

	static void start_slave_vertical_levitation(){
		data_to_change = (float) data_from_backend;
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[START_VERTICAL_LEVITATION_ORDER_ID]);
		vcu_connection->send_order(*EthernetOrders[STABLE_LEVITATION_CONFIRMATION_TCP_ORDER_INDEX]);
	}

	static void stop_slave_levitation(){
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[STOP_LEVITATION_ORDER_ID]);
	}

	static void stick_down_slave(){

	}

	static void landing_slave(){
		vcu_connection->send_order(*EthernetOrders[LANDING_COMPLETE_CONFIRMATION_TCP_ORDER_INDEX]);
	}

	static void start_slave_horizontal_levitation(){
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[START_HORIZONTAL_LEVITATION_ORDER_ID]);
	}

	static void set_new_slave_data_ready(){new_slave_data = true;}
};

#undef coil_t
#undef lpu_t
#undef coil_I
#undef bat_V
#undef airgap
#undef ldu_array_deduction
