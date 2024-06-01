#include "LCU_SLAVE.hpp"

void LDUs_zeroing(){
	bool zeroing_complete = true;
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].ldu_zeroing();
		zeroing_complete &= lcu_instance->ldu_array[i].flags.finished_zeroing;
	}
	if(zeroing_complete){
		for(int i = 0; i < LDU_COUNT; i++){
			lcu_instance->ldu_array[i].shunt_zeroing_offset = lcu_instance->ldu_array[i].average_current_for_zeroing.output_value;
		}
		lcu_instance->CalibrationCompleted = true;
		*shared_control_data.slave_secondary_status |= 1;
	}
}

void DOF5_update_airgap_data(){
	Airgaps::update_binary();
}

void DOF5_update_shunt_data(){
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].update_shunt_value();
	}
}

void DOF5_update_vbat_data(){
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].update_vbat_value();
	}
}

void DOF1_update_airgap_data(){
	Airgaps::airgaps_binary_data_array[DOF1_USED_AIRGAP_INDEX] = ADC::get_int_value(Airgaps::airgaps_index_array[DOF1_USED_AIRGAP_INDEX]);
	Airgaps::airgaps_average_binary_data_array[DOF1_USED_AIRGAP_INDEX].compute(Airgaps::airgaps_binary_data_array[DOF1_USED_AIRGAP_INDEX]);
}

void DOF1_update_shunt_data(){
	lcu_instance->ldu_array[DOF1_USED_LDU_INDEX].update_shunt_value();
}

void DOF1_update_vbat_data(){
	lcu_instance->ldu_array[DOF1_USED_LDU_INDEX].update_vbat_value();
}

void rise_current_PI_flag(){
	lcu_instance->PendingCurrentPI = true;
}

void rise_levitation_control_flag(){
	lcu_instance->PendingLevitationControl = true;
}

void rise_housekeeping_tasks_flag(){
	lcu_instance->PendingHousekeepingTasks = true;
}

void enable_all_current_controls(){
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].flags.enable_current_control = true;
		lcu_instance->ldu_array[i].flags.fixed_vbat = true;
	}
}

void disable_all_current_controls(){
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].flags.enable_current_control = false;
		lcu_instance->ldu_array[i].flags.fixed_vbat = false;
		lcu_instance->ldu_array[i].Voltage_by_current_PI.reset();
		lcu_instance->ldu_array[i].set_pwms_duty(0);
	}
}

void run_current_PI(){
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].PI_current_to_duty_cycle();
	}
}

void update_levitation_constants(float new_levitation_constants[LDU_COUNT][15]){
	for(int i = 0; i < LDU_COUNT; i++){
		for(int j = 0; j < 15; j++){
			KID_MATRIX[i][j] = -new_levitation_constants[i][j];
		}
	}
}

void start_levitation_control(){
	lcu_instance->set_desired_airgap_distance(data_to_change);
	lcu_instance->start_control();
}


void set_desired_current_on_LDU(){
	lcu_instance->ldu_array[ldu_to_change].desired_current = data_to_change;
 	disable_all_current_controls();
 	lcu_instance->ldu_array[ldu_to_change].flags.fixed_vbat = true;
 	lcu_instance->ldu_array[ldu_to_change].flags.enable_current_control = true;
}


void reset_desired_current_on_LDU(){//TODO: implement as order on GUI
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].Voltage_by_current_PI.reset();
		lcu_instance->ldu_array[i].desired_current = 0;
	}
}

void initial_order_callback(){
	if(*shared_control_data.master_running_mode == *shared_control_data.slave_running_mode && *shared_control_data.slave_secondary_status == 1){
		Communication::flags.SPIEstablished = true;
	}else{

	}
}

void test_pwm_order_callback(){
	lcu_instance->stop_control();
	if(ldu_to_change >= LDU_COUNT){return;}
	lcu_instance->ldu_array[ldu_to_change].set_pwms_duty(duty_to_change);
	lcu_instance->ldu_array[ldu_to_change].desired_current = 0;
	lcu_instance->ldu_buffers.turn_on();
}

void define_shared_data(){
	shared_control_data.master_status = new uint8_t{0};
	shared_control_data.master_secondary_status = new uint8_t{0};
	shared_control_data.master_running_mode = new uint8_t{255};
	shared_control_data.slave_status = (uint8_t*) &lcu_instance->generalStateMachine.current_state;
	shared_control_data.slave_secondary_status = new uint8_t{0};
	shared_control_data.slave_running_mode = new uint8_t{(uint8_t)RUNNING_MODE};
	for(int i = 0; i < LDU_COUNT; i++){
		shared_control_data.fixed_coil_current[i] = &(lcu_instance->ldu_array[i].binary_current_shunt);
		shared_control_data.fixed_battery_voltage[i] = &(lcu_instance->ldu_array[i].binary_battery_voltage);
		shared_control_data.shunt_zeroing_offset[i] = &(lcu_instance->ldu_array[i].shunt_zeroing_offset);
	}
	for(int i = 0;  i < AIRGAP_COUNT; i++){
		shared_control_data.fixed_airgap_distance[i] = &Airgaps::airgaps_binary_data_array[i];
		shared_control_data.float_airgap_distance[i] = &Airgaps::airgaps_data_array[i];
	}
}

void send_to_fault(){
	status_flags.fault_flag = true;
}

void shutdown(){
	lcu_instance->ldu_buffers.turn_off();
	disable_all_current_controls();
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].Voltage_by_current_PI.reset();
		lcu_instance->ldu_array[i].set_pwms_duty(0);
	}
	lcu_instance->levitationControl.stop();
}
