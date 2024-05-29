
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
	shared_control_data.master_secondary_status = new uint8_t;
	shared_control_data.master_running_mode = new uint8_t{(uint8_t)RUNNING_MODE};
	shared_control_data.slave_status = new uint8_t;
	shared_control_data.slave_secondary_status = new uint8_t;
	shared_control_data.slave_running_mode = new uint8_t{255};

	for(int i = 0;  i < LDU_COUNT; i++){
		shared_control_data.fixed_battery_voltage[i] = new uint16_t;
		shared_control_data.float_battery_voltage[i] = new float;
		shared_control_data.fixed_coil_current[i] = new uint16_t;
		shared_control_data.float_coil_current[i] = new float;
		shared_control_data.shunt_zeroing_offset[i] = new float;
	}
	for(int i = 0;  i < AIRGAP_COUNT; i++){
		shared_control_data.fixed_airgap_distance[i] = new uint16_t;
		shared_control_data.float_airgap_distance[i] = new float;
	}
}

void general_enter_fault(){
	LDU_Buffer::shutdown_buffers();
}

void initial_order_callback(){
	if(*shared_control_data.slave_secondary_status == 1 && *shared_control_data.slave_running_mode == *shared_control_data.master_running_mode){
		Communication::flags.SPIEstablished = true;
	}
}
