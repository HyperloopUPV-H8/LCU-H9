#pragma once

#include "CommonData/CommonData.hpp"
#include "LDU/LDU.hpp"

#define KP_AIRGAP_TO_CURRENT -4868.5//-5500.0
#define KI_AIRGAP_TO_CURRENT -1030.1 //-1700.0
#define KD_AIRGAP_TO_CURRENT -94.0 //-550.0
#define MOVING_AVERAGE_SIZE 20

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class Control{
public:
	arithmetic_number_type desired_airgap_distance_m = 0.0197;
	arithmetic_number_type desired_current = 0;
	PID<IntegratorType::Trapezoidal,FilterDerivatorType::Moving_Average, 22> Levitation_control_PID; /**< 1DOF only*/

	Control() : Levitation_control_PID{KP_AIRGAP_TO_CURRENT, KI_AIRGAP_TO_CURRENT, KD_AIRGAP_TO_CURRENT, LEVITATION_CONTROL_PERIOD_SECONDS}{}

	bool run_pid = false;

	void control_loop(){
		arithmetic_number_type error = desired_airgap_distance_m - Airgaps::airgaps_data_array[DOF1_USED_AIRGAP_INDEX].output_value;
		Levitation_control_PID.input(error);
		Levitation_control_PID.execute();
		desired_current = Levitation_control_PID.output_value;
		if(desired_current > MAXIMUM_DESIRED_CURRENT){
			desired_current = MAXIMUM_DESIRED_CURRENT;
		}
		if(desired_current < -MAXIMUM_DESIRED_CURRENT){
			desired_current = -MAXIMUM_DESIRED_CURRENT;
		}
	}

	void start(){
		run_pid = true;
	}

	void stop(){
		run_pid = false;
		reset();
	}

	void reset(){
		Levitation_control_PID.reset();
		desired_current = 0;
	}
};
