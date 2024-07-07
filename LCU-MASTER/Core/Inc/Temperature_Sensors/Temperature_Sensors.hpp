#pragma once

#include "CommonData/CommonData.hpp"
#include "Control/Blocks/Zeroing.hpp"

class Temperature_Sensors{
public:
	static float coil_temperature[LDU_COUNT];
	static float lpu_temperature[LDU_COUNT];

	static LinearSensor<float> coil_temperature_adc[LDU_COUNT];
	static NTC lpu_temperature_adc[LDU_COUNT];

	static uint32_t temperature_zeroing_count;

	static FloatMovingAverage<TEMPERATURE_ZEROING_SAMPLE_AMOUNT> coil_temperature_zeroing_calculator[LDU_COUNT];
	static FloatMovingAverage<TEMPERATURE_ZEROING_SAMPLE_AMOUNT> lpu_temperature_zeroing_calculator[LDU_COUNT];

	static float coil_temperature_adc_zeroing[LDU_COUNT];
	static float lpu_temperature_adc_zeroing[LDU_COUNT];

	static bool zeroing_complete;

	static void inscribe(){
		coil_temperature_adc[0] = LinearSensor(COIL_T_PIN_1,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[0]);
		coil_temperature_adc[1] = LinearSensor(COIL_T_PIN_2,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[1]);
		coil_temperature_adc[2] = LinearSensor(COIL_T_PIN_3,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[2]);
		coil_temperature_adc[3] = LinearSensor(COIL_T_PIN_4,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[3]);
		coil_temperature_adc[4] = LinearSensor(COIL_T_PIN_5,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[4]);
		coil_temperature_adc[5] = LinearSensor(COIL_T_PIN_6,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[5]);
		coil_temperature_adc[6] = LinearSensor(COIL_T_PIN_7,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[6]);
		coil_temperature_adc[7] = LinearSensor(COIL_T_PIN_8,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[7]);
		coil_temperature_adc[8] = LinearSensor(COIL_T_PIN_9,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[8]);
		coil_temperature_adc[9] = LinearSensor(COIL_T_PIN_10,TEMPERATURE_SLOPE,TEMPERATURE_OFFSET,&coil_temperature[9]);

		lpu_temperature_adc[0] = NTC(LPU_T_PIN_1,&lpu_temperature[0]);
		lpu_temperature_adc[1] = NTC(LPU_T_PIN_2,&lpu_temperature[1]);
		lpu_temperature_adc[2] = NTC(LPU_T_PIN_3,&lpu_temperature[2]);
		lpu_temperature_adc[3] = NTC(LPU_T_PIN_4,&lpu_temperature[3]);
		lpu_temperature_adc[4] = NTC(LPU_T_PIN_5,&lpu_temperature[4]);
		lpu_temperature_adc[5] = NTC(LPU_T_PIN_6,&lpu_temperature[5]);
		lpu_temperature_adc[6] = NTC(LPU_T_PIN_7,&lpu_temperature[6]);
		lpu_temperature_adc[7] = NTC(LPU_T_PIN_8,&lpu_temperature[7]);
		lpu_temperature_adc[8] = NTC(LPU_T_PIN_9,&lpu_temperature[8]);
		lpu_temperature_adc[9] = NTC(LPU_T_PIN_10,&lpu_temperature[9]);

		/*for(uint8_t i = 0; i < LDU_COUNT; i++){
		}*/
	}

	static void start(){
	}

	static void zeroing(){
		//zeroing_complete = true;
		if(zeroing_complete){return;}
		for(int i = 0; i < LDU_COUNT; i++){
			coil_temperature_adc[i].read();
			lpu_temperature_adc[i].read();
			coil_temperature_zeroing_calculator[i].compute(coil_temperature[i]);
			lpu_temperature_zeroing_calculator[i].compute(lpu_temperature[i]);
		}
		temperature_zeroing_count++;
		if(temperature_zeroing_count > TEMPERATURE_ZEROING_SAMPLE_AMOUNT){
			zeroing_complete = true;
			for(int i = 0; i < LDU_COUNT; i++){
				coil_temperature_adc_zeroing[i] = coil_temperature_zeroing_calculator[i].output_value - 25.0;
				lpu_temperature_adc_zeroing[i] = lpu_temperature_zeroing_calculator[i].output_value - 25.0;
if constexpr(POD_PROTECTIONS){
				if(abs(coil_temperature_adc_zeroing[i] + 25.0) > COIL_TEMPERATURE_ZEROING_MAXIMUM_LIMIT){
					ErrorHandler("Error on zeroing of coil %i",(i+1));
				}
				if(abs(lpu_temperature_adc_zeroing[i] + 25.0) > LPU_TEMPERATURE_ZEROING_MAXIMUM_LIMIT){
					ErrorHandler("Error on zeroing of lpu %i",(i+1));
				}
}
			}
		}
	}

	static void update(){
		for(int i = 0; i < LDU_COUNT; i++){
			coil_temperature_adc[i].read();
			lpu_temperature_adc[i].read();

			shared_control_data.float_coil_temperature[i] = coil_temperature[i] - coil_temperature_adc_zeroing[i];
			shared_control_data.float_lpu_temperature[i] = lpu_temperature[i] - lpu_temperature_adc_zeroing[i];
		}
	}
};

