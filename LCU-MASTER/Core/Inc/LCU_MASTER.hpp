#pragma once

#include "Communication/Communication.hpp"
#include "LDU_Buffer/LDU_Buffer.hpp"
#include "CommonData/CommonData.hpp"
#include "LEDs/LEDs.hpp"

class LCU;

extern LCU *lcu_instance;

class LCU{
public:
	uint8_t coil_temperature_adc_id[LDU_COUNT]{0};
	uint8_t lpu_temperature_adc_id[LDU_COUNT]{0};
	Communication communication;
	StateMachine generalStateMachine;
	StateMachine levitationStateMachine;
	LEDs leds;

	struct CommFlags{
		bool lcu_data_to_send = false;
		bool levitation_data_to_send = false;
		bool voltage_data_OBCCU_to_send = false;
	}commflags;

	LCU();
	void sensors_inscribe();
	void state_machine_definition();
	void update();
	void check_communications();


	static inline float coil_temperature_calculation(uint16_t fixed_coil_temperature){
		return fixed_coil_temperature / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}

	static inline float lpu_temperature_calculation(uint16_t lpu_coil_temperature){
		return lpu_coil_temperature / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}

	static bool initial_to_operational_transition(){
		return Communication::flags.SPIEstablished && Communication::vcu_connection->is_connected();
	}

	static bool initial_to_fault_transition(){
		return false;
	}

	static bool operational_to_fault_transition(){
		return *shared_control_data.slave_status != (uint8_t)OPERATIONAL;
	}

	static void general_enter_operational(){
		lcu_instance->leds.Set_Operational_Led();
		LDU_Buffer::ready_buffers();
	}

	static void general_enter_fault(){
		lcu_instance->leds.Set_Fault_Led();
		LDU_Buffer::shutdown_buffers();
	}

	static void levitation_enter_taking(){
		Communication::vcu_connection->send_order(*Communication::EthernetOrders[STABLE_LEVITATION_CONFIRMATION_TCP_ORDER_INDEX]);
	}
};

