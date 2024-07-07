#include "LCU_MASTER.hpp"

LCU *lcu_instance = nullptr;

LCU::LCU() : generalStateMachine(DEFINING){
	lcu_instance = this;
	sensors_inscribe();
	state_machine_definition();
	ProtectionManager::link_state_machine(generalStateMachine, FAULT);
	Communication::init();
	STLIB::start(LCU_IP.string_address);
	Temperature_Sensors::start();
	communication.define_packets();
	Communication::start();
	commflags.definition_complete = true;

}


void LCU::update(){
	STLIB::update();
	SPI::Order_update();
	generalStateMachine.check_transitions();
	ProtectionManager::check_protections();
	Communication::update();
	check_communications();
	LDU_Buffer::update_buffers();
	if(commflags.temperature_read){
		commflags.temperature_read = false;
		Temperature_Sensors::update();
	}
	if constexpr(!POD_PROTECTIONS){
		if(Communication::vcu_connection.is_connected()){
			ErrorHandler("VCU connected while LCU is not in POD mode");
		}
	}
}

void LCU::sensors_inscribe(){
	Temperature_Sensors::inscribe();

	LDU_Buffer::ldu_buffers[0] = LDU_Buffer{LCU_BUFFER_RESET_PIN_1, LCU_BUFFER_FAULT_PIN_1, LCU_BUFFER_READY_PIN_1, LCU_BUFFER_FAULT_PIN_2, LCU_BUFFER_READY_PIN_2};
	LDU_Buffer::ldu_buffers[1] = LDU_Buffer{LCU_BUFFER_RESET_PIN_2, LCU_BUFFER_FAULT_PIN_3, LCU_BUFFER_READY_PIN_3, LCU_BUFFER_FAULT_PIN_4, LCU_BUFFER_READY_PIN_4};
	LDU_Buffer::ldu_buffers[2] = LDU_Buffer{LCU_BUFFER_RESET_PIN_3, LCU_BUFFER_FAULT_PIN_5, LCU_BUFFER_READY_PIN_5, LCU_BUFFER_FAULT_PIN_6, LCU_BUFFER_READY_PIN_6};
	LDU_Buffer::ldu_buffers[3] = LDU_Buffer{LCU_BUFFER_RESET_PIN_4, LCU_BUFFER_FAULT_PIN_7, LCU_BUFFER_READY_PIN_7, LCU_BUFFER_FAULT_PIN_8, LCU_BUFFER_READY_PIN_8};
	LDU_Buffer::ldu_buffers[4] = LDU_Buffer{LCU_BUFFER_RESET_PIN_5, LCU_BUFFER_FAULT_PIN_9, LCU_BUFFER_READY_PIN_9, LCU_BUFFER_FAULT_PIN_10, LCU_BUFFER_READY_PIN_10};
}

void LCU::state_machine_definition(){
	generalStateMachine.add_state(INITIAL);
	generalStateMachine.add_state(OPERATIONAL);
	generalStateMachine.add_state(FAULT);

	generalStateMachine.add_transition(DEFINING, INITIAL, defining_to_initial_transition);
	generalStateMachine.add_transition(INITIAL, OPERATIONAL, initial_to_operational_transition);
	generalStateMachine.add_transition(INITIAL, FAULT, initial_to_fault_transition);
	generalStateMachine.add_transition(OPERATIONAL, FAULT, operational_to_fault_transition);

	generalStateMachine.add_low_precision_cyclic_action([&](){lcu_instance->commflags.lcu_data_to_send = true;}, chrono::milliseconds(ETH_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_low_precision_cyclic_action([&](){lcu_instance->commflags.voltage_data_OBCCU_to_send = true;}, chrono::milliseconds(ETH_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_low_precision_cyclic_action([&](){lcu_instance->commflags.levitation_data_to_send = true;}, chrono::milliseconds(ETH_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_low_precision_cyclic_action(Communication::lcu_initial_transaction, chrono::milliseconds(SPI_REFRESH_DATA_PERIOD_MS), INITIAL);
	generalStateMachine.add_low_precision_cyclic_action(Communication::lcu_data_transaction, chrono::milliseconds(SPI_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_low_precision_cyclic_action([&](){ErrorHandlerModel::error_to_communicate = true;}, chrono::seconds(2), {FAULT});
	generalStateMachine.add_mid_precision_cyclic_action([&](){if(!Temperature_Sensors::zeroing_complete){Temperature_Sensors::zeroing();}else{Temperature_Sensors::update();}}, std::chrono::microseconds((int) (TEMPERATURE_ZEROING_SAMPLING_PERIOD_SECONDS*1000000)), INITIAL);
	generalStateMachine.add_mid_precision_cyclic_action([&](){lcu_instance->commflags.temperature_read = true;}, std::chrono::microseconds((int) (TEMPERATURE_UPDATE_PERIOD_SECONDS*1000000)), {OPERATIONAL, FAULT});

	generalStateMachine.add_enter_action(general_enter_operational, OPERATIONAL);
	generalStateMachine.add_enter_action(general_enter_fault, FAULT);
}

void LCU::check_communications(){
	if(commflags.lcu_data_to_send){
		Communication::send_lcu_data_to_backend();
		commflags.lcu_data_to_send = false;
	}
	if(commflags.levitation_data_to_send){
		Communication::send_levitation_data_to_backend();
		commflags.levitation_data_to_send = false;
	}
	if(commflags.voltage_data_OBCCU_to_send){
		Communication::send_voltage_data_to_OBCCU();
		commflags.voltage_data_OBCCU_to_send = false;
	}
}
