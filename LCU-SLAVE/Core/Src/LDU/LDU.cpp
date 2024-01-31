#include "LDU/LDU.hpp"


LDU LDU::ldu_array[LDU_COUNT];

LDU::LDU(Pin &pwm1_pin, Pin &pwm2_pin, Pin &vbat_pin, Pin &shunt_pin){
	pwm1 = new PWM(pwm1_pin);
	pwm2 = new PWM(pwm2_pin);
	vbat_id = ADC::inscribe(vbat_pin);
	shunt_id = ADC::inscribe(shunt_pin);
}

void LDU::start(){
	pwm1->turn_on();
	pwm2->turn_on();
	ADC::turn_on(vbat_id);
	ADC::turn_on(shunt_id);
	change_pwm1_freq(PWM_FREQ_HZ);
	change_pwm2_freq(PWM_FREQ_HZ);
}

void LDU::change_pwm1_duty(float duty){
	pwm1->set_duty_cycle(duty);
}


void LDU::change_pwm2_duty(float duty){
	pwm2->set_duty_cycle(duty);
}

void LDU::change_pwm1_freq(uint32_t freq){
	pwm1->set_frequency(freq);
}

void LDU::change_pwm2_freq(uint32_t freq){
	pwm2->set_frequency(freq);
}

uint16_t LDU::get_vbat_value(){return ADC::get_int_value(vbat_id);}

uint16_t LDU::get_shunt_value(){return ADC::get_int_value(shunt_id);}
