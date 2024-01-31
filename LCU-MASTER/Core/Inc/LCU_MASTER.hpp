#pragma once

#include "Communication/Communication.hpp"
#include "CommonData/CommonData.hpp"

class LCU{
public:

	enum generalStates{
		Initial = 0,
		Operational,
		Fault,
	};

	uint8_t coil_temperature_adc_id[LDU_COUNT]{0};
	uint8_t lpu_temperature_adc_id[LDU_COUNT]{0};
	Communication communication;
	StateMachine generalStateMachine;


	LCU();
	void sensors_inscribe();
	void state_machine_definition();
	void update();


	static inline float coil_temperature_calculation(uint16_t fixed_coil_temperature){
		return fixed_coil_temperature / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}

	static inline float lpu_temperature_calculation(uint16_t lpu_coil_temperature){
		return lpu_coil_temperature / MAX_16BIT * ADC_MAX_VOLTAGE; //TODO: calculate in correct units
	}


	static bool initial_to_operational_transition(){
		return Communication::gui_connection->is_connected();
	}
};
