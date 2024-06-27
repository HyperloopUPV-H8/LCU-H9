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

		EthernetPackets[AIRGAPS_FULL_DATA_INDEX] = new StackPacket(AIRGAPS_FULL_DATA,
				airgaps_data[0],airgaps_data[1],airgaps_data[2],airgaps_data[3],airgaps_data[4],airgaps_data[5],airgaps_data[6],airgaps_data[7],airgaps_data[8],airgaps_data[9],
				airgaps_data[10],airgaps_data[11],airgaps_data[12],airgaps_data[13],airgaps_data[14],airgaps_data[15],airgaps_data[16],airgaps_data[17],airgaps_data[18],airgaps_data[19],
				airgaps_data[20],airgaps_data[21],airgaps_data[22],airgaps_data[23],airgaps_data[24],airgaps_data[25],airgaps_data[26],airgaps_data[27],airgaps_data[28],airgaps_data[29],
				airgaps_data[30],airgaps_data[31],airgaps_data[32],airgaps_data[33],airgaps_data[34],airgaps_data[35],airgaps_data[36],airgaps_data[37],airgaps_data[38],airgaps_data[39],
				airgaps_data[40],airgaps_data[41],airgaps_data[42],airgaps_data[43],airgaps_data[44],airgaps_data[45],airgaps_data[46],airgaps_data[47],airgaps_data[48],airgaps_data[49],
				airgaps_data[50],airgaps_data[51],airgaps_data[52],airgaps_data[53],airgaps_data[54],airgaps_data[55],airgaps_data[56],airgaps_data[57],airgaps_data[58],airgaps_data[59],
				airgaps_data[60],airgaps_data[61],airgaps_data[62],airgaps_data[63],airgaps_data[64],airgaps_data[65],airgaps_data[66],airgaps_data[67],airgaps_data[68],airgaps_data[69],
				airgaps_data[70],airgaps_data[71],airgaps_data[72],airgaps_data[73],airgaps_data[74],airgaps_data[75],airgaps_data[76],airgaps_data[77],airgaps_data[78],airgaps_data[79],
				airgaps_data[80],airgaps_data[81],airgaps_data[82],airgaps_data[83],airgaps_data[84],airgaps_data[85],airgaps_data[86],airgaps_data[87],airgaps_data[88],airgaps_data[89],
				airgaps_data[90],airgaps_data[91],airgaps_data[92],airgaps_data[93],airgaps_data[94],airgaps_data[95],airgaps_data[96],airgaps_data[97],airgaps_data[98],airgaps_data[99]
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
