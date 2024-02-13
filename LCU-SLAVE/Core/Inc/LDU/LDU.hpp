#pragma once

#include <CommonData/CommonData.hpp>

#define KP_CURRENT_TO_DUTY 22.9546
#define KI_CURRENT_TO_DUTY 208.3333
#define MOVING_AVERAGE_SIZE 20

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LDU{
public:
	uint8_t index = 0; /**< this index is the software index, and is one less than the hardware index, as this one starts with 0 and the hardware one starts in one */
	PWM *pwm1 = nullptr;
	PWM *pwm2 = nullptr;
	uint8_t vbat_id = 0;
	uint8_t shunt_id = 0;


	double desired_current = 0;
	double LDU_duty_cycle = 0;

	MovingAverage<MOVING_AVERAGE_SIZE> average_voltage_battery;
	MovingAverage<MOVING_AVERAGE_SIZE> average_current_shunt;
	PI<IntegratorType::Trapezoidal> Voltage_by_current_PI;




	LDU() = default;
	LDU(uint8_t index, Pin &pwm1_pin, Pin &pwm2_pin, Pin &vbat_pin, Pin &shunt_pin) : index(index), Voltage_by_current_PI{}{
		pwm1 = new PWM(pwm1_pin);
		slave_periph_pointers.ldu_pwms[index][0] = pwm1;
		pwm2 = new PWM(pwm2_pin);
		slave_periph_pointers.ldu_pwms[index][1] = pwm2;
		vbat_id = ADC::inscribe(vbat_pin);
		shunt_id = ADC::inscribe(shunt_pin);
	}


	void start(){
		pwm1->turn_on();
		pwm2->turn_on();
		ADC::turn_on(vbat_id);
		ADC::turn_on(shunt_id);
		change_pwm1_freq(PWM_FREQ_HZ);
		change_pwm2_freq(PWM_FREQ_HZ);
	}

	void update(){
		if constexpr(running_mode == GUI_CONTROL){

		}else{

		}
	}

	void change_pwm1_duty(float duty){pwm1->set_duty_cycle(duty);}
	void change_pwm2_duty(float duty){pwm2->set_duty_cycle(duty);}

	void change_pwms_duty(float duty){
		if(duty > 0){
			change_pwm2_duty(0);
			change_pwm1_duty(duty);
		}else{
			change_pwm1_duty(0);
			change_pwm2_duty(-duty);
		}
	}

	void change_pwm1_freq(uint32_t freq){pwm1->set_frequency(freq);}
	void change_pwm2_freq(uint32_t freq){pwm2->set_frequency(freq);}
	uint16_t get_vbat_value(){return ADC::get_int_value(vbat_id);}
	uint16_t get_shunt_value(){return ADC::get_int_value(shunt_id);}

	void PI_current_to_duty_cycle(){
		double desired_voltage = Voltage_by_current_PI.input(average_current_shunt.output_value);
		change_pwms_duty_cycle(calculate_duty_by_voltage());
	}

	float calculate_duty_by_voltage(double voltage){
		return voltage * 100 / average_voltage_battery.output_value;
	}
};
