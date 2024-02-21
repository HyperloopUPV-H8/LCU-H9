#pragma once

#include <CommonData/CommonData.hpp>

#define DOUBLE_AIRGAP_SLOPE 7.8112/1000
#define DOUBLE_AIRGAP_OFFSET 3.0947/1000

class Airgaps{
public:
	static uint8_t airgaps_index_array[AIRGAP_COUNT];
	static double airgaps_raw_data_array[AIRGAP_COUNT];
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
	}

	static inline void start(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			ADC::turn_on(airgaps_index_array[i]);
		}
	}

	static inline void update(){
		airgaps_raw_data_array[DOF1_USED_AIRGAP_INDEX] = ADC::get_value(airgaps_index_array[DOF1_USED_AIRGAP_INDEX]);
		airgaps_data_array[DOF1_USED_AIRGAP_INDEX].compute(airgaps_raw_data_array[DOF1_USED_AIRGAP_INDEX] * DOUBLE_AIRGAP_SLOPE + DOUBLE_AIRGAP_OFFSET);
	}

	static inline void parse_arrays(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			slave_control_data.fixed_airgap_distance[i] = ADC::get_int_value(airgaps_index_array[i]);
		}
	}
};
