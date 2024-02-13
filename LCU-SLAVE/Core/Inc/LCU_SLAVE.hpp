#include <CommonData/CommonData.hpp>
#include <Communication/Communication.hpp>
#include <LDU/LDU.hpp>
#include <Airgaps/Airgaps.hpp>

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LCU{
public:
	Communication communication;
	StateMachine generalStateMachine;
	LDU<running_mode, arithmetic_number_type> ldu_array[LDU_COUNT];

	LCU() : generalStateMachine(INITIAL){
		setup_configuration();
	}


	void start();
	void update(){
		while(ErrorHandlerModel::error_triggered){
			ErrorHandlerModel::ErrorHandlerUpdate();
		}

		for(uint8_t i = 0; i < LDU_COUNT; i++){

			uint16_t vbat = ldu_array[i].get_vbat_value();
			uint16_t shunt = ldu_array[i].get_shunt_value();

			if(vbat > 32768){
				vbat = 0;
			}
			if(shunt > 32768){
				shunt = 0;
			}
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

		Airgaps::inscribe();
		Communication::init();
		STLIB::start();
		Communication::start();
		Airgaps::turn_on();

		for(uint8_t i = 0; i < LDU_COUNT; i++){
			ldu_array[i].start();
		}
	}



/* ###################################################################################
 * ###################### STATE MACHINE DECLARATION  #################################
 * ###################################################################################
 */

	void state_machine_inscribe(){
		//################  ADDING ALL THE STATES  ##########################
		generalStateMachine.add_state(OPERATIONAL);
		generalStateMachine.add_state(FAULT);

		//################# ADDING ALL TRANSITIONS ##########################
		generalStateMachine.add_transition(INITIAL, OPERATIONAL, general_transition_initial_to_operational);
		generalStateMachine.add_transition(INITIAL, FAULT, general_transition_initial_to_fault);
		generalStateMachine.add_transition(OPERATIONAL, FAULT, general_transition_operational_to_fault);

		//################# ADDING ALL CYCLIC ACTIONS #######################
	}

	bool general_transition_initial_to_operational(){
		return true;
	}

	bool general_transition_initial_to_fault(){
		return false;
	}

	bool general_transition_operational_to_fault(){
		return false;
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
};
