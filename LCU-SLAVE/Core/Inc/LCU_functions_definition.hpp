#include "LCU_SLAVE.hpp"

void update_airgap_data(){
	Airgaps::update();
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

void rise_levitation_control_flag(){
	lcu_instance->PendingLevitationControl = true;
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
	lcu_instance->set_desired_airgap_distance(Communication::data_to_change);
	lcu_instance->start_control();
}


static void set_desired_current_on_LDU(){
 	ldu_array[Communication::ldu_to_change].desired_current = Communication::data_to_change;
	ldu_array[Communication::ldu_to_change].flags.run_pi = true;
}


static void test_pwm_order_callback(){
	/*ldu_array[Communication::ldu_to_change].flags.fixed_pwm = true;
	ldu_array[Communication::ldu_to_change].Voltage_by_current_PI.reset();*/
	lcu_instance->stop_control();
	ldu_array[Communication::ldu_to_change].change_pwms_duty(Communication::duty_to_change);
	ldu_array[Communication::ldu_to_change].desired_current = 0;
}

void send_to_fault(){
	lcu_instance->FaultFlag = true;
}

void shut_down(){
	for(int i = 0; i < LDU_COUNT; i++){
		ldu_array[i].shut_down();
	}
}
