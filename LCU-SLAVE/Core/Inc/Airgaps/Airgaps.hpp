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

	static IntegerMovingAverage<uint32_t, uint32_t, 0, CURRENT_ZEROING_SAMPLE_AMOUNT> horizontal_airgap_sumation_zeroing_5_6;
	static IntegerMovingAverage<uint32_t, uint32_t, 0, CURRENT_ZEROING_SAMPLE_AMOUNT> horizontal_airgap_sumation_zeroing_7_8;
	static uint32_t zeroing_sample_count;
	static int32_t expected_horizontal_airgap_sumation_5_6;
	static int32_t expected_horizontal_airgap_sumation_7_8;

	static bool horizontal_airgap_zeroing_complete;
	static int32_t noise;

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

	static inline void update_binary(){
		noise = 0;
		if(horizontal_airgap_zeroing_complete){
		int32_t airgap_summation_5_6 = (int32_t)*airgaps_binary_data_pointer_array[4] + (int32_t)*airgaps_binary_data_pointer_array[5];
		int32_t airgap_summation_7_8 = (int32_t)*airgaps_binary_data_pointer_array[6] + (int32_t)*airgaps_binary_data_pointer_array[7];
		if(airgap_summation_5_6 > (expected_horizontal_airgap_sumation_5_6 + HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE)){
			noise += airgap_summation_5_6 - (expected_horizontal_airgap_sumation_5_6 + HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE);
		}else if(airgap_summation_5_6 < (expected_horizontal_airgap_sumation_5_6 - HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE)){
			noise += airgap_summation_5_6 - (expected_horizontal_airgap_sumation_5_6 - HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE);
		}

		if(airgap_summation_7_8 > (expected_horizontal_airgap_sumation_7_8 + HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE)){
			noise += airgap_summation_7_8 - (expected_horizontal_airgap_sumation_7_8 + HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE);
		}else if(airgap_summation_7_8 < (expected_horizontal_airgap_sumation_7_8 - HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE)){
			noise += airgap_summation_7_8 - (expected_horizontal_airgap_sumation_7_8 - HORIZONTAL_AIRGAP_BINARY_VOLTAGE_EXPECTED_NOISE);
		}

		noise /= 4;
		}
		for(int i = 0; i < AIRGAP_COUNT; i++){
			airgaps_binary_data_array[i] = *airgaps_binary_data_pointer_array[i];
			airgaps_average_binary_data_array[i].compute(airgaps_binary_data_array[i]);
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

	static void airgap_sumation_zeroing(){
		if(horizontal_airgap_zeroing_complete){
			return;
		}
		horizontal_airgap_sumation_zeroing_5_6.compute((uint32_t)airgaps_average_binary_data_array[4].output_value + (uint32_t)airgaps_average_binary_data_array[5].output_value);
		horizontal_airgap_sumation_zeroing_7_8.compute((uint32_t)airgaps_average_binary_data_array[6].output_value + (uint32_t)airgaps_average_binary_data_array[7].output_value);
		zeroing_sample_count++;
		if(zeroing_sample_count > CURRENT_ZEROING_SAMPLE_AMOUNT){
			expected_horizontal_airgap_sumation_5_6 = (int32_t)horizontal_airgap_sumation_zeroing_5_6.output_value;
			expected_horizontal_airgap_sumation_7_8 = (int32_t)horizontal_airgap_sumation_zeroing_7_8.output_value;
			horizontal_airgap_zeroing_complete = true;
		}
	}

};
