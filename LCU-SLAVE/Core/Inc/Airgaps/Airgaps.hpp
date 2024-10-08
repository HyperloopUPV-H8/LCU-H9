#pragma once

#include <CommonData/CommonData.hpp>

/**
 * @brief this class handles the airgap sensor read and parsing, saving the results in a moving average
 */
class Airgaps{
public:
	static uint8_t airgaps_index_array[AIRGAP_COUNT];
	static uint16_t* airgaps_binary_data_pointer_array[AIRGAP_COUNT];
	static uint16_t airgaps_binary_data_array[AIRGAP_COUNT];
	static IntegerMovingAverage<uint16_t, uint16_t, 0, 10> airgaps_average_binary_data_array[AIRGAP_COUNT];
	static float airgaps_data_array[AIRGAP_COUNT];

	static bool activate_filter;
	static bool check_flags;

	static inline void inscribe(){
			airgaps_index_array[0] = ADC::inscribe(AIRGAP_PIN_1);
			airgaps_index_array[1] = ADC::inscribe(AIRGAP_PIN_2);
			airgaps_index_array[2] = ADC::inscribe(AIRGAP_PIN_3);
			airgaps_index_array[3] = ADC::inscribe(AIRGAP_PIN_4);
			airgaps_index_array[4] = ADC::inscribe(AIRGAP_PIN_5);
			airgaps_index_array[5] = ADC::inscribe(AIRGAP_PIN_6);
			airgaps_index_array[6] = ADC::inscribe(AIRGAP_PIN_7);
			airgaps_index_array[7] = ADC::inscribe(AIRGAP_PIN_8);
	}

	static inline void start(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			ADC::turn_on(airgaps_index_array[i]);
			airgaps_binary_data_pointer_array[i] = ADC::get_value_pointer(airgaps_index_array[i]);
		}
	}

	static inline void update_binary_no_filter(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_binary_data_array[i] = *airgaps_binary_data_pointer_array[i];
			airgaps_average_binary_data_array[i].compute(airgaps_binary_data_array[i]);
			check_binary_value(i);
		}
	}

	static inline void update_binary(){
		if(!activate_filter){update_binary_no_filter();return;}
		for(int i = 0; i < AIRGAP_COUNT; i++){
			uint16_t prev = airgaps_binary_data_array[i];
			airgaps_binary_data_array[i] = *airgaps_binary_data_pointer_array[i];

			/*if(airgaps_binary_data_array[i] < MINIMUM_EXPECTED_AIRGAP_VALUE_BINARY[i] ||
				airgaps_binary_data_array[i] > MAXIMUM_EXPECTED_AIRGAP_VALUE_BINARY[i]){
				airgaps_binary_data_array[i] = prev;
			}else*/ if((int32_t)airgaps_binary_data_array[i] - (int32_t)prev > MAXIMUM_EXPECTED_AIRGAP_INCREASE_BINARY[i]){
				airgaps_binary_data_array[i] = prev + MAXIMUM_EXPECTED_AIRGAP_INCREASE_BINARY[i];
			}else if((int32_t)prev - (int32_t)airgaps_binary_data_array[i] > MAXIMUM_EXPECTED_AIRGAP_INCREASE_BINARY[i]){
				airgaps_binary_data_array[i] = prev - MAXIMUM_EXPECTED_AIRGAP_INCREASE_BINARY[i];
			}
			airgaps_average_binary_data_array[i].compute(airgaps_binary_data_array[i]);
			check_binary_value(i);
		}
	}

	static inline void check_binary_value(uint8_t index){
		if(index == 5){
			return;
		}
if constexpr(POD_PROTECTIONS){
		if(check_flags && airgaps_average_binary_data_array[index].output_value <= MINIMUM_BINARY_VALUE_IN_CONNECTION){
			send_to_fault(AIRGAP_OUT_OF_RANGE+index);
		}
}
	}

	static inline void update_data(){
if constexpr(USING_1DOF){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_data_array[i] = airgaps_average_binary_data_array[i].output_value * ADC_BINARY_TO_VOLTAGE * FLOAT_1DOF_AIRGAP_SLOPE + FLOAT_1DOF_AIRGAP_OFFSET;
		}
}
if constexpr(USING_5DOF && !IS_HIL){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_data_array[i] = airgap_distance_binary_to_float(i, airgaps_average_binary_data_array[i].output_value);
		}
}
if constexpr(IS_HIL){
		for(int i = 0; i < AIRGAP_COUNT/2; i++){
			airgaps_data_array[i] = airgaps_average_binary_data_array[i].output_value * ADC_BINARY_TO_VOLTAGE * FLOAT_HEMS_HIL_AIRGAP_SLOPE + FLOAT_HEMS_HIL_AIRGAP_OFFSET;
			airgaps_data_array[i+AIRGAP_COUNT/2] = airgaps_average_binary_data_array[i].output_value * ADC_BINARY_TO_VOLTAGE * FLOAT_EMS_HIL_AIRGAP_SLOPE + FLOAT_EMS_HIL_AIRGAP_OFFSET;
		}
}
	}

	static inline float get_airgap_data(uint16_t airgap_index){
		return airgaps_data_array[airgap_index];
	}

};
