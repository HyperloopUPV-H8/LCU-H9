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
		if(Communication::flags.SPIEstablished){
			return Communication::vcu_connection->is_connected();
		}
		return false;
	}

	static bool initial_to_fault_transition(){
		return false;
	}

	static bool operational_to_fault_transition(){
		if(*shared_control_data.slave_status == (uint8_t)FAULT){
			ErrorHandler("Slave gone into fault");
			return true;
		}
		return !(Communication::vcu_connection->is_connected()) ;
	}
};

