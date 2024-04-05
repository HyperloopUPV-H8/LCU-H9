#pragma once

#include <CommonData/CommonData.hpp>

/**
 * @brief this class handles the airgap sensor read and parsing, saving the results in a moving average
 */
class Airgaps{
public:
	static uint8_t airgaps_index_array[AIRGAP_COUNT];
	static uint16_t airgaps_binary_data_array[AIRGAP_COUNT];
	static float airgaps_raw_data_array[AIRGAP_COUNT];
	static MovingAverage<AIRGAP_MOVING_AVERAGE_COUNT> airgaps_data_array[AIRGAP_COUNT];

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
				shared_control_data.float_airgap_distance[i] = &airgaps_raw_data_array[i];
			}
	}

	static inline void start(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			ADC::turn_on(airgaps_index_array[i]);
		}
	}

	static inline void update(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_binary_data_array[i] = ADC::get_int_value(airgaps_index_array[i]);
			airgaps_raw_data_array[i] = ADC::get_value(airgaps_index_array[i]);
			airgaps_data_array[i].compute((double)airgaps_raw_data_array[i] * DOUBLE_AIRGAP_SLOPE + DOUBLE_AIRGAP_OFFSET);
		}
	}

	static inline void parse_arrays(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			*shared_control_data.fixed_airgap_distance[i] = ADC::get_int_value(airgaps_index_array[i]);
		}
	}
};
