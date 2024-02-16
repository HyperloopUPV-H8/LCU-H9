#include "LCU_SLAVE.hpp"

static void update_airgap_data(){
	/*for(int i = 0; i < AIRGAP_COUNT; i++){
	}*/
}


static void update_shunt_data(){
	for(int i = 9; i < LDU_COUNT; i++){
		ldu_array[i].update_raw_shunt_value();
	}
}


static void update_vbat_data(){
	for(int i = 9; i < LDU_COUNT; i++){
		ldu_array[i].update_raw_vbat_value();
	}
}


void rise_current_PI_flag(){
	lcu_instance->PendingCurrentPI = true;
}

static void rise_housekeeping_tasks_flag(){
	lcu_instance->PendingHousekeepingTasks = true;
}

static void run_current_PI(){
	for(int i = 9; i < LDU_COUNT; i++){
		ldu_array[i].PI_current_to_duty_cycle();
	}
}


static void set_vbat_on_LDU(){
	//ldu_array[Communication::ldu_to_change].voltage_battery = Communication::data_to_change;
 	ldu_array[Communication::ldu_to_change].desired_current = Communication::data_to_change;
	ldu_array[Communication::ldu_to_change].flags.run_pi = true;
	ldu_array[Communication::ldu_to_change].flags.fixed_pwm = false;
}


static void set_desired_current_on_LDU(){
	ldu_array[Communication::ldu_to_change].desired_current = Communication::data_to_change;
	ldu_array[Communication::ldu_to_change].flags.fixed_desired_current = true;
}


static void test_pwm_order_callback(){
	ldu_array[Communication::ldu_to_change].change_pwms_duty(Communication::duty_to_change);
	ldu_array[Communication::ldu_to_change].flags.fixed_pwm = true;
	ldu_array[Communication::ldu_to_change].Voltage_by_current_PI.reset();
}

void send_to_fault(){
	lcu_instance->FaultFlag = true;
}

void shut_down(){
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].shut_down();
	}
}
