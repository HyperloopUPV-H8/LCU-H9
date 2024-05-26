#include "LCU_SLAVE.hpp"

void DOF5_update_airgap_data(){
	Airgaps::update_binary();
}

void DOF5_update_shunt_data(){
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].update_shunt_value();
	}
}

void DOF5_update_vbat_data(){
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].update_vbat_value();
	}
}

void DOF1_update_airgap_data(){
	Airgaps::airgaps_binary_data_array[DOF1_USED_AIRGAP_INDEX] = ADC::get_int_value(Airgaps::airgaps_index_array[DOF1_USED_AIRGAP_INDEX]);
	Airgaps::airgaps_average_binary_data_array[DOF1_USED_AIRGAP_INDEX].compute(Airgaps::airgaps_binary_data_array[DOF1_USED_AIRGAP_INDEX]);
}

void DOF1_update_shunt_data(){

	ldu_array[DOF1_USED_LDU_INDEX].update_shunt_value();
}

void DOF1_update_vbat_data(){
	ldu_array[DOF1_USED_LDU_INDEX].update_vbat_value();
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

void run_current_PI(){
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].PI_current_to_duty_cycle();
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
 	ldu_array[ldu_to_change].desired_current = data_to_change;
	status_flags.enable_current_control = true;
}


void reset_desired_current_on_LDU(){//TODO: implement as order on GUI
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].Voltage_by_current_PI.reset();
		ldu_array[i].desired_current = 0;
	}
}

void initial_order_callback(){
	/*if(master_status == RUNNING_MODE){
		Communication::flags.SPIEstablished = true;
	}else{
		ErrorHandler("Slave and master are not in the same mode");
	}*/
}

void test_pwm_order_callback(){
	lcu_instance->stop_control();
	if(ldu_to_change >= LDU_COUNT){return;}
	ldu_array[ldu_to_change].set_pwms_duty(duty_to_change);
	ldu_array[ldu_to_change].desired_current = 0;
}

void send_to_fault(){
	status_flags.fault_flag = true;
}

void shutdown(){
	lcu_instance->ldu_buffers.turn_off();
	status_flags.enable_current_control = false;
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].Voltage_by_current_PI.reset();
		ldu_array[i].set_pwms_duty(0);
	}
	lcu_instance->levitationControl.stop();
}
