#pragma once

#include <CommonData/CommonData.hpp>

class LDU{
public:
	static LDU ldu_array[LDU_COUNT];
	PWM *pwm1 = nullptr;
	PWM *pwm2 = nullptr;
	uint8_t vbat_id = 0;
	uint8_t shunt_id = 0;


	float LDU_duty_cycle = 0;


	LDU() = default;
	LDU(Pin &pwm1_pin, Pin &pwm2_pin, Pin &vbat_pin, Pin &shunt_pin);
	void start();
	void change_pwm1_duty(float duty);
	void change_pwm2_duty(float duty);
	void change_pwm1_freq(uint32_t freq);
	void change_pwm2_freq(uint32_t freq);
	uint16_t get_vbat_value();
	uint16_t get_shunt_value();

	static void change_ldu_duty_cycle(uint16_t ldu_index, float ldu_duty_cycle){
		if(ldu_index > 9){
			return;
		}
		if(ldu_duty_cycle > 0){
			ldu_array[ldu_index].change_pwm2_duty(0);
			ldu_array[ldu_index].change_pwm1_duty(ldu_duty_cycle);
		}else{
			ldu_array[ldu_index].change_pwm1_duty(0);
			ldu_array[ldu_index].change_pwm2_duty(-ldu_duty_cycle);
		}
	}
};
