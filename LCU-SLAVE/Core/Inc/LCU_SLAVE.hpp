#pragma once

#include <CommonData/CommonData.hpp>
#include <Communication/Communication.hpp>
#include <LDU/LDU.hpp>
#include <Airgaps/Airgaps.hpp>
#include <Control/Control.hpp>
#include "PWM_Buffer/PWM_Buffer.hpp"

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LCU;

static LCU<RUNNING_MODE, ARITHMETIC_MODE> *lcu_instance = nullptr;

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LCU{
public:
	Communication communication;
	Control<running_mode, arithmetic_number_type> levitationControl;
	StateMachine generalStateMachine;
	PWM_Buffer ldu_buffers;

	bool PendingCurrentPI = false;
	bool PendingLevitationControl = false;
	bool PendingHousekeepingTasks = false;


	uint64_t LevitationControlCount = 0;
	uint64_t CurrentPICount = 0;

	LCU() : generalStateMachine(INITIAL){
		if(lcu_instance == nullptr){	lcu_instance = this;
		}else{		ErrorHandler("tried to set a second lcu");		}
		setup_configuration();
	}

	void update(){
		generalStateMachine.check_transitions();
		//ProtectionManager::check_protections();
		Communication::update();

if constexpr(USING_1DOF){
		DOF1_update();
}
if constexpr(USING_5DOF){
		DOF5_update();
}
	}


	void DOF5_update(){
		if(PendingLevitationControl){

			if(status_flags.enable_levitation_control){
				LevitationControlCount++;
				levitationControl.DOF5_control_loop();
				levitationControl.update_desired_current_control();
			}
			PendingLevitationControl = false;
		}

		if(PendingCurrentPI){
			CurrentPICount++;
			run_current_PI();
			PendingCurrentPI = false;
		}
	}

	void DOF1_update(){
		if(PendingLevitationControl){
			if(status_flags.enable_levitation_control){
				LevitationControlCount++;
				levitationControl.DOF1_control_loop();
				ldu_array[DOF1_USED_LDU_INDEX].desired_current = levitationControl.desired_current;
			}
			PendingLevitationControl = false;
		}

		if(PendingCurrentPI){
			CurrentPICount++;
			run_current_PI();
			PendingCurrentPI = false;
		}
	}

	void setup_configuration(){
		//index is n but uses the n+1 hardware data, as hardware starts with 1 instead of 0.
if constexpr(USING_1DOF){
		ldu_array[0] = LDU<running_mode, arithmetic_number_type>(0, PWM_PIN_1_1, PWM_PIN_1_2, VBAT_PIN_1, SHUNT_PIN_1, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[1] = LDU<running_mode, arithmetic_number_type>(1, PWM_PIN_2_1, PWM_PIN_2_2, VBAT_PIN_2, SHUNT_PIN_2, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[2] = LDU<running_mode, arithmetic_number_type>(2, PWM_PIN_3_1, PWM_PIN_3_2, VBAT_PIN_3, SHUNT_PIN_3, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[3] = LDU<running_mode, arithmetic_number_type>(3, PWM_PIN_4_1, PWM_PIN_4_2, VBAT_PIN_4, SHUNT_PIN_4, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[4] = LDU<running_mode, arithmetic_number_type>(4, PWM_PIN_5_1, PWM_PIN_5_2, VBAT_PIN_5, SHUNT_PIN_5, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[5] = LDU<running_mode, arithmetic_number_type>(5, PWM_PIN_6_1, PWM_PIN_6_2, VBAT_PIN_6, SHUNT_PIN_6, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[6] = LDU<running_mode, arithmetic_number_type>(6, PWM_PIN_7_1, PWM_PIN_7_2, VBAT_PIN_7, SHUNT_PIN_7, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[7] = LDU<running_mode, arithmetic_number_type>(7, PWM_PIN_8_1, PWM_PIN_8_2, VBAT_PIN_8, SHUNT_PIN_8, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[8] = LDU<running_mode, arithmetic_number_type>(8, PWM_PIN_9_1, PWM_PIN_9_2, VBAT_PIN_9, SHUNT_PIN_9, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
		ldu_array[9] = LDU<running_mode, arithmetic_number_type>(9, PWM_PIN_10_1, PWM_PIN_10_2, VBAT_PIN_10, SHUNT_PIN_10, KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY);
}
if constexpr(USING_5DOF){
		ldu_array[0] = LDU<running_mode, arithmetic_number_type>(0, PWM_PIN_1_1, PWM_PIN_1_2, VBAT_PIN_1, SHUNT_PIN_1, KP_HEMS_CURRENT_TO_DUTY, KI_HEMS_CURRENT_TO_DUTY);
		ldu_array[1] = LDU<running_mode, arithmetic_number_type>(1, PWM_PIN_2_1, PWM_PIN_2_2, VBAT_PIN_2, SHUNT_PIN_2, KP_HEMS_CURRENT_TO_DUTY, KI_HEMS_CURRENT_TO_DUTY);
		ldu_array[2] = LDU<running_mode, arithmetic_number_type>(2, PWM_PIN_3_1, PWM_PIN_3_2, VBAT_PIN_3, SHUNT_PIN_3, KP_HEMS_CURRENT_TO_DUTY, KI_HEMS_CURRENT_TO_DUTY);
		ldu_array[3] = LDU<running_mode, arithmetic_number_type>(3, PWM_PIN_4_1, PWM_PIN_4_2, VBAT_PIN_4, SHUNT_PIN_4, KP_HEMS_CURRENT_TO_DUTY, KI_HEMS_CURRENT_TO_DUTY);
		ldu_array[4] = LDU<running_mode, arithmetic_number_type>(4, PWM_PIN_5_1, PWM_PIN_5_2, VBAT_PIN_5, SHUNT_PIN_5, KP_EMS_CURRENT_TO_DUTY, KI_EMS_CURRENT_TO_DUTY);
		ldu_array[5] = LDU<running_mode, arithmetic_number_type>(5, PWM_PIN_6_1, PWM_PIN_6_2, VBAT_PIN_6, SHUNT_PIN_6, KP_EMS_CURRENT_TO_DUTY, KI_EMS_CURRENT_TO_DUTY);
		ldu_array[6] = LDU<running_mode, arithmetic_number_type>(6, PWM_PIN_7_1, PWM_PIN_7_2, VBAT_PIN_7, SHUNT_PIN_7, KP_EMS_CURRENT_TO_DUTY, KI_EMS_CURRENT_TO_DUTY);
		ldu_array[7] = LDU<running_mode, arithmetic_number_type>(7, PWM_PIN_8_1, PWM_PIN_8_2, VBAT_PIN_8, SHUNT_PIN_8, KP_EMS_CURRENT_TO_DUTY, KI_EMS_CURRENT_TO_DUTY);
		ldu_array[8] = LDU<running_mode, arithmetic_number_type>(8, PWM_PIN_9_1, PWM_PIN_9_2, VBAT_PIN_9, SHUNT_PIN_9, KP_EMS_CURRENT_TO_DUTY, KI_EMS_CURRENT_TO_DUTY);
		ldu_array[9] = LDU<running_mode, arithmetic_number_type>(9, PWM_PIN_10_1, PWM_PIN_10_2, VBAT_PIN_10, SHUNT_PIN_10, KP_EMS_CURRENT_TO_DUTY, KI_EMS_CURRENT_TO_DUTY);
}
		state_machine_initialization();
		//protections_inscribe();
		Airgaps::inscribe();
		Communication::init();

		STLIB::start();
		Airgaps::start();
		Communication::start();

		for(uint8_t i = 0; i < LDU_COUNT; i++){
			ldu_array[i].start();
		}

		communication.define_packets();
	}



/* ###################################################################################
 * ###################### STATE MACHINE DECLARATION  #################################
 * ###################################################################################
 */

	void state_machine_initialization(){
		//################  ADDING ALL THE STATES  ##########################
		generalStateMachine.add_state(OPERATIONAL);
		generalStateMachine.add_state(FAULT);

		//################# ADDING ALL TRANSITIONS ##########################
		generalStateMachine.add_transition(INITIAL, OPERATIONAL, general_transition_initial_to_operational);
		generalStateMachine.add_transition(INITIAL, FAULT, general_transition_initial_to_fault);
		generalStateMachine.add_transition(OPERATIONAL, FAULT, general_transition_operational_to_fault);

		//################# ADDING ALL CYCLIC ACTIONS #######################
if constexpr(USING_5DOF){
		generalStateMachine.add_high_precision_cyclic_action(DOF5_update_shunt_data, std::chrono::microseconds((int) (CURRENT_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_high_precision_cyclic_action(DOF5_update_airgap_data, std::chrono::microseconds((int) (AIRGAP_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_low_precision_cyclic_action(DOF5_update_vbat_data, std::chrono::microseconds((int) (VBAT_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
}
if constexpr(USING_1DOF){
		generalStateMachine.add_high_precision_cyclic_action(DOF1_update_shunt_data, std::chrono::microseconds((int) (CURRENT_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_high_precision_cyclic_action(DOF1_update_airgap_data, std::chrono::microseconds((int) (AIRGAP_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_low_precision_cyclic_action(DOF1_update_vbat_data, std::chrono::microseconds((int) (VBAT_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
}
		generalStateMachine.add_mid_precision_cyclic_action(rise_current_PI_flag, std::chrono::microseconds((int) (CURRENT_CONTROL_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_low_precision_cyclic_action(rise_levitation_control_flag,  std::chrono::microseconds((int) (LEVITATION_CONTROL_PERIOD_SECONDS*1000000)), OPERATIONAL);

		//###############  ADDING ALL TRANSITION CALLBACKS  ###################
		generalStateMachine.add_enter_action(general_enter_operational, OPERATIONAL);
		generalStateMachine.add_enter_action(general_enter_fault, FAULT);
	}

	void protections_inscribe(){
		//ProtectionManager::link_state_machine(generalStateMachine, FAULT);
	}

	static bool general_transition_initial_to_operational(){
		return true;
	}

	static bool general_transition_initial_to_fault(){
		return false;
	}

	static bool general_transition_operational_to_fault(){
		return status_flags.fault_flag;
	}

	static void general_enter_operational(){
		lcu_instance->ldu_buffers.turn_on();
	}

	static void general_enter_fault(){
		shutdown();
	}

	/* #############################################################################
	 * ###################### UTILITY FUNCTIONS ####################################
	 * #############################################################################
	 */

	void set_desired_airgap_distance(float desired_airgap_distance){
		levitationControl.desired_airgap_distance_m = desired_airgap_distance;
	}

	void start_control(){
		status_flags.enable_current_control = true;
		levitationControl.start();
	}

	void stop_control(){
		shutdown();
		status_flags.enable_levitation_control = false;
		for(int i = 0; i < LDU_COUNT; i++){
			ldu_array[i].Voltage_by_current_PI.reset();
		}
		levitationControl.stop();
	}
};
