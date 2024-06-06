#include "LCU_MASTER.hpp"

LCU *lcu_instance = nullptr;

LCU::LCU() : generalStateMachine(INITIAL){
	lcu_instance = this;
	sensors_inscribe();
	state_machine_definition();
	ProtectionManager::link_state_machine(generalStateMachine, FAULT);
	Communication::init();
	STLIB::start(LCU_IP.string_address);

	for(uint8_t i = 0; i < LDU_COUNT; i++){
		ADC::turn_on(coil_temperature_adc_id[i]);
		ADC::turn_on(lpu_temperature_adc_id[i]);
	}
	communication.define_packets();
	Communication::start();

}


void LCU::update(){
	STLIB::update();
	SPI::Order_update();
	generalStateMachine.check_transitions();
	ProtectionManager::check_protections();
	Communication::update();
	LDU_Buffer::update_buffers();
	for(int i = 0; i < LDU_COUNT; i++){ //TODO: abstract these sensors
		shared_control_data.fixed_lpu_temperature[i] = ADC::get_int_value(lpu_temperature_adc_id[i]);
		shared_control_data.float_lpu_temperature[i] = lpu_temperature_calculation(shared_control_data.fixed_lpu_temperature[i]);
		shared_control_data.fixed_coil_temperature[i] = ADC::get_int_value(coil_temperature_adc_id[i]);
		shared_control_data.float_coil_temperature[i] = coil_temperature_calculation(shared_control_data.fixed_coil_temperature[i]);
	}
}

void LCU::sensors_inscribe(){
	coil_temperature_adc_id[0] = ADC::inscribe(COIL_T_PIN_1);
	coil_temperature_adc_id[1] = ADC::inscribe(COIL_T_PIN_2);
	coil_temperature_adc_id[2] = ADC::inscribe(COIL_T_PIN_3);
	coil_temperature_adc_id[3] = ADC::inscribe(COIL_T_PIN_4);
	coil_temperature_adc_id[4] = ADC::inscribe(COIL_T_PIN_5);
	coil_temperature_adc_id[5] = ADC::inscribe(COIL_T_PIN_6);
	coil_temperature_adc_id[6] = ADC::inscribe(COIL_T_PIN_7);
	coil_temperature_adc_id[7] = ADC::inscribe(COIL_T_PIN_8);
	coil_temperature_adc_id[8] = ADC::inscribe(COIL_T_PIN_9);
	coil_temperature_adc_id[9] = ADC::inscribe(COIL_T_PIN_10);

	lpu_temperature_adc_id[0] = ADC::inscribe(LPU_T_PIN_1);
	lpu_temperature_adc_id[1] = ADC::inscribe(LPU_T_PIN_2);
	lpu_temperature_adc_id[2] = ADC::inscribe(LPU_T_PIN_3);
	lpu_temperature_adc_id[3] = ADC::inscribe(LPU_T_PIN_4);
	lpu_temperature_adc_id[4] = ADC::inscribe(LPU_T_PIN_5);
	lpu_temperature_adc_id[5] = ADC::inscribe(LPU_T_PIN_6);
	lpu_temperature_adc_id[6] = ADC::inscribe(LPU_T_PIN_7);
	lpu_temperature_adc_id[7] = ADC::inscribe(LPU_T_PIN_8);
	lpu_temperature_adc_id[8] = ADC::inscribe(LPU_T_PIN_9);
	lpu_temperature_adc_id[9] = ADC::inscribe(LPU_T_PIN_10);

	LDU_Buffer::ldu_buffers[0] = LDU_Buffer{LCU_BUFFER_RESET_PIN_1, LCU_BUFFER_FAULT_PIN_1, LCU_BUFFER_READY_PIN_1, LCU_BUFFER_FAULT_PIN_2, LCU_BUFFER_READY_PIN_2};
	LDU_Buffer::ldu_buffers[1] = LDU_Buffer{LCU_BUFFER_RESET_PIN_2, LCU_BUFFER_FAULT_PIN_3, LCU_BUFFER_READY_PIN_3, LCU_BUFFER_FAULT_PIN_4, LCU_BUFFER_READY_PIN_4};
	LDU_Buffer::ldu_buffers[2] = LDU_Buffer{LCU_BUFFER_RESET_PIN_3, LCU_BUFFER_FAULT_PIN_5, LCU_BUFFER_READY_PIN_5, LCU_BUFFER_FAULT_PIN_6, LCU_BUFFER_READY_PIN_6};
	LDU_Buffer::ldu_buffers[3] = LDU_Buffer{LCU_BUFFER_RESET_PIN_4, LCU_BUFFER_FAULT_PIN_7, LCU_BUFFER_READY_PIN_7, LCU_BUFFER_FAULT_PIN_8, LCU_BUFFER_READY_PIN_8};
	LDU_Buffer::ldu_buffers[4] = LDU_Buffer{LCU_BUFFER_RESET_PIN_5, LCU_BUFFER_FAULT_PIN_9, LCU_BUFFER_READY_PIN_9, LCU_BUFFER_FAULT_PIN_10, LCU_BUFFER_READY_PIN_10};
}

void LCU::state_machine_definition(){
	generalStateMachine.add_state(OPERATIONAL);
	generalStateMachine.add_state(FAULT);

	generalStateMachine.add_transition(INITIAL, OPERATIONAL, initial_to_operational_transition);
	generalStateMachine.add_transition(OPERATIONAL, FAULT, operational_to_fault_transition);

	generalStateMachine.add_low_precision_cyclic_action(Communication::send_lcu_data_to_backend, chrono::milliseconds(ETH_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_low_precision_cyclic_action(Communication::send_levitation_data_to_backend, chrono::milliseconds(ETH_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_low_precision_cyclic_action(Communication::lcu_initial_transaction, chrono::milliseconds(SPI_REFRESH_DATA_PERIOD_MS), INITIAL);
	generalStateMachine.add_low_precision_cyclic_action(Communication::lcu_data_transaction, chrono::milliseconds(SPI_REFRESH_DATA_PERIOD_MS), {OPERATIONAL, FAULT});
	generalStateMachine.add_enter_action(general_enter_operational, OPERATIONAL);
	generalStateMachine.add_enter_action(general_enter_fault, FAULT);
}

