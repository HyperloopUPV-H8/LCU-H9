
#include "CommonData/CommonData.hpp"
#include "LCU_MASTER.hpp"

void fix_buffer_reset_high(){
	Communication::ldu_index_to_change = Communication::ldu_number_to_change - 1;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset = true;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset_value = true;
}

void fix_buffer_reset_low(){
	Communication::ldu_index_to_change = Communication::ldu_number_to_change - 1;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset = true;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset_value = false;
}

void define_shared_data(){
	shared_control_data.master_status = (uint8_t*) &(lcu_instance->generalStateMachine.current_state);
	shared_control_data.master_secondary_status = new uint8_t{0};
	shared_control_data.master_running_mode = new uint8_t{(uint8_t)RUNNING_MODE};
	shared_control_data.slave_status = new uint8_t{0};
	shared_control_data.slave_secondary_status = new uint8_t{0};
	shared_control_data.slave_running_mode = new uint8_t{255};
	shared_control_data.current_control_count = new uint32_t{0};
	shared_control_data.levitation_control_count = new uint32_t{0};

	for(int i = 0;  i < LDU_COUNT; i++){
		shared_control_data.fixed_battery_voltage[i] = new uint16_t{0};
		shared_control_data.float_battery_voltage[i] = new float{0.0};
		shared_control_data.fixed_coil_current[i] = new uint16_t{0};
		shared_control_data.float_coil_current[i] = new float{0.0};
		shared_control_data.shunt_zeroing_offset[i] = new float{0.0};
		shared_control_data.float_current_ref[i] = new float{0.0};
	}
	for(int i = 0; i < 5; i++){
		shared_control_data.float_airgap_to_pos[i] = new float{0.0};
		shared_control_data.float_airgap_to_pos_der[i] = new float{0.0};
		shared_control_data.float_airgap_to_pos_in[i] = new float{0.0};
	}
	for(int i = 0;  i < AIRGAP_COUNT; i++){
		shared_control_data.fixed_airgap_distance[i] = new uint16_t{0};
		shared_control_data.float_airgap_distance[i] = new float{0.0};
	}
}

void general_enter_operational(){
	lcu_instance->leds.Set_Operational_Led();
}

void general_enter_fault(){
	lcu_instance->leds.Set_Fault_Led();
	if(ProtectionManager::external_trigger){
		Communication::lcu_data_transaction();
		lcu_instance->levitationStateMachine.force_change_state(DISCHARGING);
	}else{
		LDU_Buffer::shutdown_buffers();
		lcu_instance->levitationStateMachine.force_change_state(IDLE);
	}
	ProtectionManager::propagate_fault();
}

void levitation_enter_idle(){
	lcu_instance->commflags.timer_to_idle_flag = false;
	Communication::stop_slave_levitation();
}

void external_enter_discharging(){
	lcu_instance->levitationStateMachine.force_change_state(DISCHARGING);
}

void levitation_enter_discharging(){
	Communication::send_discharge();
	lcu_instance->set_timer_to_idle(13000);
}

void initial_order_callback(){
	if(*shared_control_data.slave_secondary_status == 1 && *shared_control_data.slave_running_mode == *shared_control_data.master_running_mode){
		Communication::flags.SPIEstablished = true;
	}
}
