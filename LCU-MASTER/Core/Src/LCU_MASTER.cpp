#include "LCU_MASTER.hpp"

LCU::LCU() : generalStateMachine(Initial){
	sensors_inscribe();
	state_machine_definition();
	Communication::init();
	STLIB::start(MASTER_IP.string_address);

	for(uint8_t i = 0; i < LDU_COUNT; i++){
		ADC::turn_on(coil_temperature_adc_id[i]);
		ADC::turn_on(lpu_temperature_adc_id[i]);
	}
	Communication::start();
}


void LCU::update(){
	STLIB::update();
	SPI::Order_update();
	generalStateMachine.check_transitions();
	Communication::update();
	for(int i = 0; i < LDU_COUNT; i++){
		master_control_data.fixed_lpu_temperature[i] = ADC::get_int_value(lpu_temperature_adc_id[i]);
		master_control_data.lpu_temperature[i] = lpu_temperature_calculation(master_control_data.fixed_lpu_temperature[i]);
		master_control_data.fixed_coil_temperature[i] = ADC::get_int_value(coil_temperature_adc_id[i]);
		master_control_data.coil_temperature[i] = coil_temperature_calculation(master_control_data.fixed_coil_temperature[i]);
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
}

void LCU::state_machine_definition(){
	generalStateMachine.add_state(Operational);
	generalStateMachine.add_state(Fault);

	generalStateMachine.add_transition(Initial, Operational, initial_to_operational_transition);

	generalStateMachine.add_low_precision_cyclic_action(Communication::send_lcu_data_to_backend, chrono::milliseconds(ETH_REFRESH_DATA_PERIOD_MS), Operational);
}

