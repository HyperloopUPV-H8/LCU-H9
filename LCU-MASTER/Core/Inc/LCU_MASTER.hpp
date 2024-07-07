#pragma once

#include "Communication/Communication.hpp"
#include "LDU_Buffer/LDU_Buffer.hpp"
#include "CommonData/CommonData.hpp"
#include "LEDs/LEDs.hpp"
#include "Temperature_Sensors/Temperature_Sensors.hpp"

class LCU;

extern LCU *lcu_instance;

class LCU{
public:
	Communication communication;
	StateMachine generalStateMachine;
	LEDs leds;

	struct CommFlags{
		bool lcu_data_to_send = false;
		bool levitation_data_to_send = false;
		bool voltage_data_OBCCU_to_send = false;
		bool definition_complete = false;
		bool temperature_read = false;
	}commflags;

	LCU();
	void sensors_inscribe();
	void state_machine_definition();
	void update();
	void check_communications();

	static bool defining_to_initial_transition(){
		return lcu_instance->commflags.definition_complete;
	}

	static bool initial_to_operational_transition(){
		if(Communication::flags.SPIEstablished && Temperature_Sensors::zeroing_complete){
if constexpr(POD_PROTECTIONS){
			return Communication::vcu_connection->is_connected();
}
			return true;
		}
		return false;
	}

	static bool initial_to_fault_transition(){
		if(*shared_control_data.slave_status == (uint8_t)FAULT){
			slave_error_parser(shared_control_data.error_code);
		}
		return false;
	}

	static bool operational_to_fault_transition(){
		if(*shared_control_data.slave_status == (uint8_t)FAULT){
			slave_error_parser(shared_control_data.error_code);
		}
		return false;
	}

	static void slave_error_parser(uint16_t error_code){
		std::unordered_map<uint16_t,string>::const_iterator got = error_codes_messages.find(error_code);
		if(got == error_codes_messages.end()){
			ErrorHandler("Error code %i not found in error code map",error_code);
		}else{
			ErrorHandler(got->second);
		}
	}
};

