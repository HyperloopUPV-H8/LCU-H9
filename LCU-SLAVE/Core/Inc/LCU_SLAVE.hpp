#pragma once

#include <CommonData/CommonData.hpp>
#include <Communication/Communication.hpp>
#include <LDU/LDU.hpp>
#include <Airgaps/Airgaps.hpp>
#include <Control/Control.hpp>

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LCU;

static LCU<RUNNING_MODE, ARITHMETIC_MODE> *lcu_instance = nullptr;

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LCU{
public:
	Communication communication;
	Control<running_mode, arithmetic_number_type> levitationControl;
	StateMachine generalStateMachine;

	bool PendingCurrentPI = false;
	bool PendingLevitationControl = false;
	bool PendingHousekeepingTasks = false;
	bool FaultFlag = false;


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

		if(PendingLevitationControl){
			LevitationControlCount++;
			if(levitationControl.run_pid){
				levitationControl.control_loop();
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
		ldu_array[0] = LDU<running_mode, arithmetic_number_type>(0, PWM_PIN_1_1, PWM_PIN_1_2, VBAT_PIN_1, SHUNT_PIN_1);
		ldu_array[1] = LDU<running_mode, arithmetic_number_type>(1, PWM_PIN_2_1, PWM_PIN_2_2, VBAT_PIN_2, SHUNT_PIN_2);
		ldu_array[2] = LDU<running_mode, arithmetic_number_type>(2, PWM_PIN_3_1, PWM_PIN_3_2, VBAT_PIN_3, SHUNT_PIN_3);
		ldu_array[3] = LDU<running_mode, arithmetic_number_type>(3, PWM_PIN_4_1, PWM_PIN_4_2, VBAT_PIN_4, SHUNT_PIN_4);
		ldu_array[4] = LDU<running_mode, arithmetic_number_type>(4, PWM_PIN_5_1, PWM_PIN_5_2, VBAT_PIN_5, SHUNT_PIN_5);
		ldu_array[5] = LDU<running_mode, arithmetic_number_type>(5, PWM_PIN_6_1, PWM_PIN_6_2, VBAT_PIN_6, SHUNT_PIN_6);
		ldu_array[6] = LDU<running_mode, arithmetic_number_type>(6, PWM_PIN_7_1, PWM_PIN_7_2, VBAT_PIN_7, SHUNT_PIN_7);
		ldu_array[7] = LDU<running_mode, arithmetic_number_type>(7, PWM_PIN_8_1, PWM_PIN_8_2, VBAT_PIN_8, SHUNT_PIN_8);
		ldu_array[8] = LDU<running_mode, arithmetic_number_type>(8, PWM_PIN_9_1, PWM_PIN_9_2, VBAT_PIN_9, SHUNT_PIN_9);
		ldu_array[9] = LDU<running_mode, arithmetic_number_type>(9, PWM_PIN_10_1, PWM_PIN_10_2, VBAT_PIN_10, SHUNT_PIN_10);

		state_machine_initialization();
		//protections_inscribe();
		Airgaps::inscribe();
		Communication::init();

		STLIB::start();
		Airgaps::start();
		Communication::start();

		communication.define_packets();

		for(uint8_t i = 0; i < LDU_COUNT; i++){
			ldu_array[i].start();
		}
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
		generalStateMachine.add_high_precision_cyclic_action(update_shunt_data, std::chrono::microseconds((int) (CURRENT_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_high_precision_cyclic_action(update_airgap_data, std::chrono::microseconds((int) (AIRGAP_UPDATE_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_low_precision_cyclic_action(update_vbat_data, std::chrono::microseconds((int) (10000)), OPERATIONAL);
		generalStateMachine.add_mid_precision_cyclic_action(rise_current_PI_flag, std::chrono::microseconds((int) (CURRENT_CONTROL_PERIOD_SECONDS*1000000)), OPERATIONAL);
		generalStateMachine.add_low_precision_cyclic_action(rise_levitation_control_flag,  std::chrono::microseconds((int) (LEVITATION_CONTROL_PERIOD_SECONDS*1000000)), OPERATIONAL);

		//###############  ADDING ALL TRANSITION CALLBACKS  ###################
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
		return lcu_instance->FaultFlag;
	}

	static void general_enter_fault(){
		shut_down();
		ldu_array[9].change_pwms_duty(0);
	}

	/* #############################################################################
	 * ###################### UTILITY FUNCTIONS ####################################
	 * #############################################################################
	 */

	void change_ldu_duty_cycle(uint16_t ldu_index, float ldu_duty_cycle){
		if(ldu_index >= LDU_COUNT){
			return;
		}
		ldu_array[ldu_index].change_pwms_duty(ldu_duty_cycle);
	}

	void set_desired_airgap_distance(arithmetic_number_type desired_airgap_distance){
		levitationControl.desired_airgap_distance_m = desired_airgap_distance;
	}

	void start_control(){
		ldu_array[DOF1_USED_LDU_INDEX].flags.run_pi = true;
		levitationControl.start();
	}

	void stop_control(){
		ldu_array[DOF1_USED_LDU_INDEX].change_pwms_duty(0);
		ldu_array[DOF1_USED_LDU_INDEX].flags.run_pi = false;
		ldu_array[DOF1_USED_LDU_INDEX].Voltage_by_current_PI.reset();
		levitationControl.stop();
	}
};
