#pragma once

#include <CommonData/CommonData.hpp>

class Airgaps{
public:
	static uint8_t index_array[AIRGAP_COUNT];

	static inline void inscribe(){
			index_array[0] = ADC::inscribe(AIRGAP_PIN_1);
			index_array[1] = ADC::inscribe(AIRGAP_PIN_2);
			index_array[2] = ADC::inscribe(AIRGAP_PIN_3);
			index_array[3] = ADC::inscribe(AIRGAP_PIN_4);
			index_array[4] = ADC::inscribe(AIRGAP_PIN_5);
			index_array[5] = ADC::inscribe(AIRGAP_PIN_6);
			index_array[6] = ADC::inscribe(AIRGAP_PIN_7);
			index_array[7] = ADC::inscribe(AIRGAP_PIN_8);
	}

	static inline void turn_on(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			ADC::turn_on(index_array[i]);
		}
	}

	static inline void parse_arrays(){
		for(int i = 0; i < AIRGAP_COUNT; i++){
			slave_control_data.fixed_airgap_distance[i] = ADC::get_int_value(index_array[i]);
		}
	}
};
