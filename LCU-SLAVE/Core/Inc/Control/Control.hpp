#pragma once

#include "CommonData/CommonData.hpp"
#include "LDU/LDU.hpp"

#define Y_POSITION_INDEX 0
#define Z_POSITION_INDEX 1
#define X_ROTATION_INDEX 2
#define Y_ROTATION_INDEX 3
#define Z_ROTATION_INDEX 4

#define DOF5_DERIVATOR_DECLARATION SimpleFloatDerivator(LEVITATION_CONTROL_PERIOD_SECONDS)
#define DOF5_INTEGRATOR_DECLARATION FloatIntegrator<IntegratorType::Trapezoidal>(LEVITATION_CONTROL_PERIOD_SECONDS,1)


float KID_MATRIX[LDU_COUNT][15] = {0};

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class Control{
public:
	//1DOF struct
	float desired_airgap_distance_m = 0.0197;
	float desired_current = 0;
	PID<IntegratorType::Trapezoidal,FilterDerivatorType::Moving_Average, LEVITATION_CONTROL_DOF1_MOVING_AVERAGE_SIZE> Levitation_control_PID; /**< 1DOF only*/


	//5DOF struct
	float position_error_data[5]{0.0};
	float position_z = 0.0;
	SimpleFloatDerivator position_error_data_derivative[5]{DOF5_DERIVATOR_DECLARATION, DOF5_DERIVATOR_DECLARATION, DOF5_DERIVATOR_DECLARATION, DOF5_DERIVATOR_DECLARATION, DOF5_DERIVATOR_DECLARATION};
	FloatIntegrator<IntegratorType::Trapezoidal> position_error_data_integral[5]{DOF5_INTEGRATOR_DECLARATION,DOF5_INTEGRATOR_DECLARATION,DOF5_INTEGRATOR_DECLARATION,DOF5_INTEGRATOR_DECLARATION,DOF5_INTEGRATOR_DECLARATION};
	MovingAverage<LEVITATION_CONTROL_DOF5_DERIVATIVE_MOVING_AVERAGE_SIZE> derivative_moving_average[5]{};
	float levitation_data_vector[15];
	float desired_current_vector[LDU_COUNT];
	MatrixMultiplier<10,15,1> KID_calculator;


	Control() : Levitation_control_PID{KP_DOF1_AIRGAP_TO_CURRENT, KI_DOF1_AIRGAP_TO_CURRENT, KD_DOF1_AIRGAP_TO_CURRENT, LEVITATION_CONTROL_PERIOD_SECONDS},
				KID_calculator(KID_MATRIX, levitation_data_vector, desired_current_vector){
		update_levitation_constants(initial_levitation_control_constants);
	}

	void DOF1_control_loop(){
		Airgaps::update_data();
		float error = desired_airgap_distance_m - Airgaps::get_airgap_data(DOF1_USED_AIRGAP_INDEX);
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

	void airgap_to_pos(){
		Airgaps::update_data();
		position_error_data[X_ROTATION_INDEX] = (asin((Airgaps::get_airgap_data(0) - Airgaps::get_airgap_data(1)) / (2*POD_CENTER_DISTANCE_Y_TO_AIRGAP_Z))
										+ asin((Airgaps::get_airgap_data(2) - Airgaps::get_airgap_data(3)) / (2*POD_CENTER_DISTANCE_Y_TO_AIRGAP_Z)))/2;

		position_error_data[Y_ROTATION_INDEX] = (asin((Airgaps::get_airgap_data(0) - Airgaps::get_airgap_data(2)) / (2*POD_CENTER_DISTANCE_X_TO_AIRGAP_Z))
										+ asin((Airgaps::get_airgap_data(1) - Airgaps::get_airgap_data(3)) / (2*POD_CENTER_DISTANCE_X_TO_AIRGAP_Z)))/2;

		position_error_data[Z_ROTATION_INDEX] = (asin((Airgaps::get_airgap_data(4) - Airgaps::get_airgap_data(6)) / (2*POD_CENTER_DISTANCE_X_TO_AIRGAP_Y))
										+ asin((Airgaps::get_airgap_data(7) - Airgaps::get_airgap_data(5)) / (2*POD_CENTER_DISTANCE_X_TO_AIRGAP_Y)))/2;

		float cos_rot_z = cos(position_error_data[Z_ROTATION_INDEX]);
		float sin_rot_z = sin(position_error_data[Z_ROTATION_INDEX]);
		float sin_rot_y = sin(position_error_data[Y_ROTATION_INDEX]);
		float cos_rot_x = cos(position_error_data[X_ROTATION_INDEX]);
		float sin_rot_x = sin(position_error_data[X_ROTATION_INDEX]);

		position_error_data[Y_POSITION_INDEX] = (Airgaps::get_airgap_data(4) - POD_CENTER_TO_L_DISTANCE+(-POD_CENTER_DISTANCE_X_TO_AIRGAP_Y * sin_rot_z + POD_CENTER_DISTANCE_Y_TO_AIRGAP_Y * cos_rot_z - POD_CENTER_DISTANCE_Z_TO_AIRGAP_Y * sin_rot_x)
										-Airgaps::get_airgap_data(5) + POD_CENTER_TO_L_DISTANCE - ( POD_CENTER_DISTANCE_X_TO_AIRGAP_Y * sin_rot_z + POD_CENTER_DISTANCE_Y_TO_AIRGAP_Y * cos_rot_z + POD_CENTER_DISTANCE_Z_TO_AIRGAP_Y * sin_rot_x)
										+Airgaps::get_airgap_data(6) - POD_CENTER_TO_L_DISTANCE + ( POD_CENTER_DISTANCE_X_TO_AIRGAP_Y * sin_rot_z + POD_CENTER_DISTANCE_Y_TO_AIRGAP_Y * cos_rot_z - POD_CENTER_DISTANCE_Z_TO_AIRGAP_Y * sin_rot_x)
										-Airgaps::get_airgap_data(7) + POD_CENTER_TO_L_DISTANCE - (-POD_CENTER_DISTANCE_X_TO_AIRGAP_Y * sin_rot_z + POD_CENTER_DISTANCE_Y_TO_AIRGAP_Y * cos_rot_z + POD_CENTER_DISTANCE_Z_TO_AIRGAP_Y * sin_rot_x))/4;

		 position_z =(Airgaps::get_airgap_data(0) - POD_CENTER_TO_SR_DISTANCE + (-POD_CENTER_DISTANCE_Y_TO_AIRGAP_Z * sin_rot_x - POD_CENTER_DISTANCE_X_TO_AIRGAP_Z * sin_rot_y - POD_CENTER_DISTANCE_Z_TO_AIRGAP_Z * cos_rot_x)
										+ Airgaps::get_airgap_data(1) - POD_CENTER_TO_SR_DISTANCE + ( POD_CENTER_DISTANCE_Y_TO_AIRGAP_Z * sin_rot_x - POD_CENTER_DISTANCE_X_TO_AIRGAP_Z * sin_rot_y - POD_CENTER_DISTANCE_Z_TO_AIRGAP_Z * cos_rot_x)
										+ Airgaps::get_airgap_data(2) - POD_CENTER_TO_SR_DISTANCE + (-POD_CENTER_DISTANCE_Y_TO_AIRGAP_Z * sin_rot_x + POD_CENTER_DISTANCE_X_TO_AIRGAP_Z * sin_rot_y - POD_CENTER_DISTANCE_Z_TO_AIRGAP_Z * cos_rot_x)
										+ Airgaps::get_airgap_data(3) - POD_CENTER_TO_SR_DISTANCE + ( POD_CENTER_DISTANCE_Y_TO_AIRGAP_Z * sin_rot_x + POD_CENTER_DISTANCE_X_TO_AIRGAP_Z * sin_rot_y - POD_CENTER_DISTANCE_Z_TO_AIRGAP_Z * cos_rot_x))/(-4);

		float prev =  position_error_data[Z_POSITION_INDEX];
		position_error_data[Z_POSITION_INDEX] = position_z - desired_airgap_distance_m; //substracts the reference of levitation distance, only for Z pos as all other references are 0
		if(position_error_data[Z_POSITION_INDEX]-prev>MAXIMUM_EXPECTED_Z_INCREASE && Airgaps::activate_filter){
			position_error_data[Z_POSITION_INDEX] = prev + MAXIMUM_EXPECTED_Z_INCREASE;
		}
	}

	void DOF5_control_loop(){
		for(int i = 0; i < 5; i++){
			position_error_data_derivative[i].input(position_error_data[i]);
			position_error_data_derivative[i].execute();
			derivative_moving_average[i].compute(position_error_data_derivative[i].output_value);
			position_error_data_integral[i].input(position_error_data[i]);
			position_error_data_integral[i].execute();
			levitation_data_vector[i*2] = position_error_data[i];
			levitation_data_vector[i*2+1] = derivative_moving_average[i].output_value;
			levitation_data_vector[i+10] = position_error_data_integral[i].output_value;
		}

		KID_calculator.execute();

		if(!status_flags.enable_lateral_levitation_control){
			for(int i = 4; i < LDU_COUNT; i++){ //for all EMS
				desired_current_vector[i] = desired_current;
			}
		}else{
			for(int i = 4; i < LDU_COUNT; i++){ //for all EMS
				if(desired_current_vector[i] < 0.0){
					desired_current_vector[i] = 0.0; //negative currents still attract in EMS, so they just get negated.
				}
			}
		}
	}

	void prepare_derivator_buffer(){
		airgap_to_pos();
		for(int i = 0; i < 5; i++){
			position_error_data_derivative[i].input(position_error_data[i]);
			position_error_data_derivative[i].execute();
		}
	}

	void start(){
		status_flags.enable_lateral_levitation_control = true; //TODO: change when this is enabled
		status_flags.enable_levitation_control = true;
		prepare_derivator_buffer(); //TODO: still testing if this is better or not
	}

	void start_vertical(){
		status_flags.enable_lateral_levitation_control = false;
		status_flags.enable_levitation_control = true;
		prepare_derivator_buffer();
	}

	void start_horizontal(){
		desired_current = 0.0;
		status_flags.enable_lateral_levitation_control = true;
		reset_horizontal();
		position_error_data_derivative[Z_ROTATION_INDEX].input(position_error_data[Z_ROTATION_INDEX]);
		position_error_data_derivative[Z_ROTATION_INDEX].execute();
		position_error_data_derivative[Y_POSITION_INDEX].input(position_error_data[Y_POSITION_INDEX]);
		position_error_data_derivative[Y_POSITION_INDEX].execute();
	}

	void enter_booster(){
		desired_current = 20.0;
		status_flags.enable_lateral_levitation_control = false;
	}

	void stop(){
		status_flags.enable_levitation_control = false;
		status_flags.enable_lateral_levitation_control = false;
		reset();
	}

	void reset(){
		Levitation_control_PID.reset();
		for(int i = 0; i < 5; i++){
			position_error_data_derivative[i].reset();
			position_error_data_integral[i].reset();
		}
		desired_current = 0.0;
	}

	void reset_horizontal(){
		position_error_data_derivative[Z_ROTATION_INDEX].reset();
		position_error_data_integral[Z_ROTATION_INDEX].reset();
		position_error_data_derivative[Y_POSITION_INDEX].reset();
		position_error_data_integral[Y_POSITION_INDEX].reset();
	}

};
