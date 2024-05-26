#pragma once

#include "ST-LIB.hpp"
#include "CommonData/CommonData.hpp"

#define coil_t shared_control_data.fixed_coil_temperature
#define lpu_t shared_control_data.fixed_lpu_temperature
#define coil_I shared_control_data.fixed_coil_current
#define bat_V shared_control_data.fixed_battery_voltage
#define airgap shared_control_data.fixed_airgap_distance
#define ldu_array_deduction uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t
#define airgap_array_deduction uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t

class Communication{
public:
	static uint8_t spi_id;
	static ServerSocket *gui_connection;
	static DatagramSocket *udp_connection;
	static DigitalOutput* test_order_received;

	static Order* EthernetOrders[ETH_ORDER_COUNT];
	static Packet* EthernetPackets[ETH_PACKET_COUNT];
	SPIStackOrder* SPIOrders[SPI_ORDER_COUNT];
	SPIBasePacket* SPIPackets[SPI_ORDER_COUNT*2];


	static struct communication_flags{
		bool SPIStart = false;
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
		for(int i = 0;  i < LDU_COUNT; i++){
			shared_control_data.fixed_battery_voltage[i] = new uint16_t;
			shared_control_data.float_battery_voltage[i] = new float;
			shared_control_data.fixed_coil_current[i] = new uint16_t;
			shared_control_data.float_coil_current[i] = new float;
		}
		for(int i = 0;  i < AIRGAP_COUNT; i++){
			shared_control_data.fixed_airgap_distance[i] = new uint16_t;
			shared_control_data.float_airgap_distance[i] = new float;
		}
		/*shared_control_data.master_status = initial_exchange_value();

		SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2] = new SPIPacket<2, uint8_t>(&master_status);
		SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2] = new SPIPacket<2, uint8_t>(&slave_status);
		SPIOrders[MASTER_SLAVE_INITIAL_ORDER_INDEX] = new SPIStackOrder(MASTER_SLAVE_INITIAL_ORDER_ID, *SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2], *SPIPackets[MASTER_SLAVE_INITIAL_ORDER_INDEX*2+1]);
		SPIOrders[MASTER_SLAVE_INITIAL_ORDER_INDEX]->set_callback(initial_order_callback);*/


		SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2] = new SPIPacket<41, uint8_t, ldu_array_deduction, ldu_array_deduction>(
				&shared_control_data.master_status,
				&coil_t[0], &coil_t[1], &coil_t[2], &coil_t[3], &coil_t[4], &coil_t[5], &coil_t[6], &coil_t[7], &coil_t[8], &coil_t[9],
				&lpu_t[0], &lpu_t[1], &lpu_t[2], &lpu_t[3], &lpu_t[4], &lpu_t[5], &lpu_t[6], &lpu_t[7], &lpu_t[8], &lpu_t[9]
		);
		SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2+1] = new SPIPacket<59, uint8_t, ldu_array_deduction, ldu_array_deduction, airgap_array_deduction>(
				&shared_control_data.slave_status,
				coil_I[0], coil_I[1], coil_I[2], coil_I[3], coil_I[4], coil_I[5], coil_I[6], coil_I[7], coil_I[8], coil_I[9],
				bat_V[0], bat_V[1], bat_V[2], bat_V[3], bat_V[4], bat_V[5], bat_V[6], bat_V[7], bat_V[8], bat_V[9],
				airgap[0], airgap[1], airgap[2], airgap[3], airgap[4], airgap[5], airgap[6], airgap[7]
		);
		SPIOrders[MASTER_SLAVE_DATA_ORDER_INDEX] = new SPIStackOrder(MASTER_SLAVE_DATA_ORDER_ID, *SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2], *SPIPackets[MASTER_SLAVE_DATA_ORDER_INDEX*2+1]);


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
	}

	static void start(){
		start_ethernet();
	}

	static void start_ethernet(){
		gui_connection = new ServerSocket(MASTER_IP, TCP_SERVER_PORT);
		udp_connection = new DatagramSocket(MASTER_IP, UDP_PORT, BACKEND, UDP_PORT);
		EthernetPackets[SEND_LPU_TEMPERATURES_TCP_PACKET_INDEX] = new StackPacket(SEND_LPU_TEMPERATURES_TCP_PACKET_ID,
				&shared_control_data.float_lpu_temperature[0],&shared_control_data.float_lpu_temperature[1],&shared_control_data.float_lpu_temperature[2],
				&shared_control_data.float_lpu_temperature[3],&shared_control_data.float_lpu_temperature[4],&shared_control_data.float_lpu_temperature[5],
				&shared_control_data.float_lpu_temperature[6],&shared_control_data.float_lpu_temperature[7],&shared_control_data.float_lpu_temperature[8],
				&shared_control_data.float_lpu_temperature[9]);

		EthernetPackets[SEND_LCU_DATA_TCP_PACKET_INDEX] = new StackPacket(SEND_LCU_DATA_TCP_PACKET_ID,
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

		EthernetOrders[TEST_PWM_TCP_ORDER_INDEX] = new StackOrder(TEST_PWM_TCP_ORDER_ID, send_pwm_data_from_backend, &ldu_number_to_change, &duty_to_change);
		EthernetOrders[START_LEVITATION_CONTROL_TCP_ORDER_INDEX] = new StackOrder(START_LEVITATION_CONTROL_TCP_ORDER_ID, start_slave_levitation_control, &data_from_backend);
		EthernetOrders[TEST_DESIRED_CURRENT_TCP_ORDER_INDEX] = new StackOrder(TEST_DESIRED_CURRENT_TCP_ORDER_ID, send_desired_current_data_from_backend, &ldu_number_to_change, &data_from_backend);
		EthernetOrders[TEST_START_RESET_TCP_ORDER_INDEX] = new StackOrder<2,uint16_t>(TEST_START_RESET_TCP_ORDER_ID, fix_buffer_reset_high, &ldu_number_to_change);
		EthernetOrders[TEST_STOP_RESET_TCP_ORDER_INDEX] = new StackOrder<2,uint16_t>(TEST_STOP_RESET_TCP_ORDER_ID, fix_buffer_reset_low, &ldu_number_to_change);
	}

	static void update(){
if constexpr(USING_1DOF){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			*shared_control_data.float_airgap_distance[i] = DOF1_airgap_distance_binary_to_float(*shared_control_data.fixed_airgap_distance[i])*1000;
		}
		for(int i = 0; i < LDU_COUNT; i++){
			*shared_control_data.float_coil_current[i] = coil_current_binary_to_real(*shared_control_data.fixed_coil_current[i]);
			*shared_control_data.float_battery_voltage[i] = battery_voltage_binary_to_real(*shared_control_data.fixed_battery_voltage[i]);
		}
}
if constexpr(USING_5DOF){
		for(int i = 0; i < AIRGAP_COUNT/2; i++){
			*shared_control_data.float_airgap_distance[i] = HEMS_airgap_distance_binary_to_float(*shared_control_data.fixed_airgap_distance[i])*1000;
			*shared_control_data.float_airgap_distance[i+AIRGAP_COUNT/2] = EMS_airgap_distance_binary_to_float(*shared_control_data.fixed_airgap_distance[i+AIRGAP_COUNT/2])*1000;
		}
		for(int i = 0; i < LDU_COUNT; i++){
			*shared_control_data.float_coil_current[i] = coil_current_binary_to_real(*shared_control_data.fixed_coil_current[i]);
			*shared_control_data.float_battery_voltage[i] = battery_voltage_binary_to_real(*shared_control_data.fixed_battery_voltage[i]);
		}
}
	}

	//###################  PERIODIC FUNCTIONS  #########################

	static void send_lcu_data_to_backend(){
		udp_connection->send_packet(*EthernetPackets[SEND_LCU_DATA_TCP_PACKET_INDEX]);
	}

	static void lcu_data_transaction(){
		SPI::master_transmit_Order(spi_id, SPIBaseOrder::SPIOrdersByID[MASTER_SLAVE_DATA_ORDER_ID]);
	}

	//#####################  SPI ORDERS CALLBACKS #######################

	static inline void end_first_spi_transaction(){
		flags.SPIStart = true;
	}



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

	static void set_new_slave_data_ready(){new_slave_data = true;}
};

#undef coil_t
#undef lpu_t
#undef coil_I
#undef bat_V
#undef airgap
#undef ldu_array_deduction
