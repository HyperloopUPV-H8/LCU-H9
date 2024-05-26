#pragma once

#include <CommonData/CommonData.hpp>

/**
 * @brief this class handles the airgap sensor read and parsing, saving the results in a moving average
 */
class Airgaps{
public:
	static uint8_t airgaps_index_array[AIRGAP_COUNT];
	static uint16_t airgaps_binary_data_array[AIRGAP_COUNT];
	static IntegerMovingAverage<uint16_t, uint16_t, 0, 10> airgaps_average_binary_data_array[AIRGAP_COUNT];
	static float airgaps_data_array[AIRGAP_COUNT];

	static inline void inscribe(){
			airgaps_index_array[0] = ADC::inscribe(AIRGAP_PIN_1);
			airgaps_index_array[1] = ADC::inscribe(AIRGAP_PIN_2);
			airgaps_index_array[2] = ADC::inscribe(AIRGAP_PIN_3);
			airgaps_index_array[3] = ADC::inscribe(AIRGAP_PIN_4);
			airgaps_index_array[4] = ADC::inscribe(AIRGAP_PIN_5);
			airgaps_index_array[5] = ADC::inscribe(AIRGAP_PIN_6);
			airgaps_index_array[6] = ADC::inscribe(AIRGAP_PIN_7);
			airgaps_index_array[7] = ADC::inscribe(AIRGAP_PIN_8);

			for(int i = 0;  i < AIRGAP_COUNT; i++){
				shared_control_data.fixed_airgap_distance[i] = &airgaps_binary_data_array[i];
				shared_control_data.float_airgap_distance[i] = &airgaps_data_array[i];
			}
	}

	static inline void start(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			ADC::turn_on(airgaps_index_array[i]);
		}
	}

	static inline void update_binary(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_binary_data_array[i] = ADC::get_int_value(airgaps_index_array[i]);
			airgaps_average_binary_data_array[i].compute(airgaps_binary_data_array[i]);
		}
	}

	static inline void update_data(){
if constexpr(USING_1DOF){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_data_array[i] = airgaps_average_binary_data_array[i].output_value * ADC_BINARY_TO_VOLTAGE * FLOAT_1DOF_AIRGAP_SLOPE + FLOAT_1DOF_AIRGAP_OFFSET;
		}
}
if constexpr(USING_5DOF){
		for(int i = 0; i < AIRGAP_COUNT/2; i++){
			airgaps_data_array[i] = airgaps_average_binary_data_array[i].output_value * ADC_BINARY_TO_VOLTAGE * FLOAT_HEMS_AIRGAP_SLOPE + FLOAT_HEMS_AIRGAP_OFFSET;
			airgaps_data_array[i+AIRGAP_COUNT/2] = airgaps_average_binary_data_array[i+AIRGAP_COUNT/2].output_value * ADC_BINARY_TO_VOLTAGE * FLOAT_EMS_AIRGAP_SLOPE + FLOAT_EMS_AIRGAP_OFFSET;
		}
}
	}

	static inline float get_airgap_data(uint16_t airgap_index){
		return airgaps_data_array[airgap_index];
	}

};
