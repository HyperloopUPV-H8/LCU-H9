#include "LCU_SLAVE.hpp"

void LDUs_zeroing(){
#if USING_HIL
		for(int i = 0; i < LDU_COUNT; i++){
			lcu_instance->ldu_array[i].shunt_zeroing_offset = 0.0;
		}
		lcu_instance->CalibrationCompleted = true;
		*shared_control_data.slave_secondary_status |= 1;
		return;
#endif
	if(lcu_instance->CalibrationCompleted){return;}
	bool zeroing_complete = true;
	for(int i = 0; i < LDU_COUNT; i++){
		lcu_instance->ldu_array[i].ldu_zeroing();
		zeroing_complete = zeroing_complete && lcu_instance->ldu_array[i].flags.finished_zeroing;
	}

	if(zeroing_complete){
		Airgaps::check_flags = true;
		for(int i = 0; i < LDU_COUNT; i++){

#if USING_CURRENT_ZEROING_LIMIT
			if(abs(lcu_instance->ldu_array[i].average_current_for_zeroing.output_value) > CURRENT_ZEROING_MAXIMUM_LIMIT){
				send_to_fault(LDU_ZEROING_FAILED + i);
			}
#endif

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
		if(i == 0 || i == 5)continue;
		lcu_instance->ldu_array[i].update_vbat_value();
	}
	lcu_instance->ldu_array[0].binary_average_battery_voltage.output_value = (lcu_instance->ldu_array[1].binary_average_battery_voltage.output_value + lcu_instance->ldu_array[2].binary_average_battery_voltage.output_value)/2;
	lcu_instance->ldu_array[5].binary_average_battery_voltage.output_value = (lcu_instance->ldu_array[6].binary_average_battery_voltage.output_value  + lcu_instance->ldu_array[7].binary_average_battery_voltage.output_value)/2;

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
		lcu_instance->ldu_array[i].disable_current_control();
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

void start_vertical_levitation(){
	lcu_instance->set_desired_airgap_distance(data_to_change);
	lcu_instance->start_vertical_control();
}

void start_horizontal_levitation(){
	lcu_instance->start_horizontal_control();
}


void set_desired_current_on_LDU(){
 	disable_all_current_controls();
 	lcu_instance->ldu_array[ldu_to_change].desired_current = data_to_change;
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
	if(*shared_control_data.master_running_mode == *shared_control_data.slave_running_mode)
	{
		if (*shared_control_data.slave_secondary_status == 1){
			Communication::flags.SPIEstablished = true;
		}
	}else{
		send_to_fault(MASTER_NOT_IN_SAME_MODE);
	}
}

void test_pwm_order_callback(){
	lcu_instance->stop_control();
	if(ldu_to_change >= LDU_COUNT){return;}
	lcu_instance->ldu_array[ldu_to_change].set_pwms_duty(duty_to_change);
	lcu_instance->ldu_array[ldu_to_change].desired_current = 0;
	lcu_instance->ldu_buffers.turn_on();
}

void set_stable_levitation_callback(){
	Airgaps::activate_filter = true;
}

void set_unstable_levitation_callback(){
	Airgaps::activate_filter = false;
}

void enter_booster_callback(){
	lcu_instance->enter_booster();
}

void define_shared_data(){
	shared_control_data.master_status = new uint8_t{0};
	shared_control_data.master_secondary_status = new uint8_t{0};
	shared_control_data.master_running_mode = new uint8_t{255};
	shared_control_data.slave_status = (uint8_t*) &lcu_instance->generalStateMachine.current_state;
	shared_control_data.slave_secondary_status = new uint8_t{0};
	shared_control_data.slave_running_mode = new uint8_t{(uint8_t)RUNNING_MODE};
	shared_control_data.current_control_count = &lcu_instance->CurrentPICount;
	shared_control_data.levitation_control_count = &lcu_instance->LevitationControlCount;
	for(int i = 0; i < LDU_COUNT; i++){
		shared_control_data.fixed_coil_current[i] = &(lcu_instance->ldu_array[i].binary_average_current_shunt.output_value);
		shared_control_data.fixed_battery_voltage[i] = &(lcu_instance->ldu_array[i].binary_average_battery_voltage.output_value);
		shared_control_data.shunt_zeroing_offset[i] = &(lcu_instance->ldu_array[i].shunt_zeroing_offset);
		shared_control_data.float_current_ref[i] =  &(lcu_instance->ldu_array[i].desired_current);
	}
	for(int i = 0; i < 5; i++){
		shared_control_data.float_airgap_to_pos[i] = &(lcu_instance->levitationControl.position_error_data[i]);
		shared_control_data.float_airgap_to_pos_der[i] = &(lcu_instance->levitationControl.position_error_data_derivative[i].output_value);
		shared_control_data.float_airgap_to_pos_in[i] = &(lcu_instance->levitationControl.position_error_data_integral[i].output_value);
	}
	shared_control_data.float_airgap_to_pos[Z_POSITION_INDEX] = &(lcu_instance->levitationControl.position_z); //overwrites to use the position instead of the position error
	for(int i = 0;  i < AIRGAP_COUNT; i++){
		shared_control_data.fixed_airgap_distance[i] = &(Airgaps::airgaps_average_binary_data_array[i].output_value);
		shared_control_data.float_airgap_distance[i] = &Airgaps::airgaps_data_array[i];
	}
}

void send_to_fault(uint16_t error_code){
	if(shared_control_data.error_code == 0){
		shared_control_data.error_code = error_code;
	}
	status_flags.fault_flag = true;
	shutdown();
}

void shutdown(){
	lcu_instance->ldu_buffers.turn_off();
	lcu_instance->levitationControl.stop();
	disable_all_current_controls();
}

void activate_discharge_callback(){
uint8_t id = Time::set_timeout(100, [&](){
	active_discharge_in_fault = true;
	if constexpr(POD_PROTECTIONS){
		lcu_instance->ldu_buffers.turn_on();
		disable_all_current_controls();
		lcu_instance->ldu_array[6].desired_current = 5.0;
		lcu_instance->ldu_array[6].flags.disabled_LDU = false;
		lcu_instance->ldu_array[6].enable_current_control();
		lcu_instance->ldu_array[7].desired_current = 5.0;
		lcu_instance->ldu_array[7].flags.disabled_LDU = false;
		lcu_instance->ldu_array[7].enable_current_control();
		lcu_instance->ldu_array[6].flags.fixed_vbat = false;
		lcu_instance->ldu_array[7].flags.fixed_vbat = false;
	}
});
Time::set_timeout(13000,[&](){
	active_discharge_in_fault = false;
	lcu_instance->ldu_array[6].desired_current =0.0;
	lcu_instance->ldu_array[6].disable_current_control();
	lcu_instance->ldu_array[7].desired_current =0.0;
	lcu_instance->ldu_array[7].disable_current_control();
});
}
