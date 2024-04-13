#pragma once

#include <CommonData/CommonData.hpp>

#define KP_CURRENT_TO_DUTY 10.0 //22.9546
#define KI_CURRENT_TO_DUTY 400.0 //208.3333
#define MOVING_AVERAGE_SIZE 20

#define DOUBLE_VBAT_SLOPE 180.29 //91.325
#define DOUBLE_VBAT_OFFSET -18.524 //-9.3784

#define DOUBLE_SHUNT_SLOPE -34.3
#define DOUBLE_SHUNT_OFFSET 67.1

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LDU{
public:
	uint8_t index = 0; /**< this index is the software index, and is one less than the hardware index, as this one starts with 0 and the hardware one starts in one */
	PWM *pwm1 = nullptr;
	PWM *pwm2 = nullptr;
	uint8_t vbat_id = 0;
	uint8_t shunt_id = 0;


	arithmetic_number_type desired_current = 0;
	arithmetic_number_type LDU_duty_cycle = 0;

	PI<IntegratorType::Trapezoidal> Voltage_by_current_PI;

	MovingAverage<10> raw_average_voltage_battery;
	arithmetic_number_type voltage_battery = 0;
	arithmetic_number_type raw_current_shunt = 0;
	arithmetic_number_type current_shunt = 0;


	struct LDU_flags{
		bool fixed_vbat = false;
		bool fixed_desired_current = false;
		bool run_pi = false;
	}flags;


	LDU() = default;
	LDU(uint8_t index, Pin &pwm1_pin, Pin &pwm2_pin, Pin &vbat_pin, Pin &shunt_pin) : index(index), Voltage_by_current_PI{KP_CURRENT_TO_DUTY, KI_CURRENT_TO_DUTY, CURRENT_CONTROL_PERIOD_SECONDS}{
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


	//################  DATA STORING, PROCESSING AND PARSING  ###################
	void update_raw_vbat_value(){
		double raw_voltage_battery = (double)ADC::get_value(vbat_id);
		raw_average_voltage_battery.compute(raw_voltage_battery);
	}

	arithmetic_number_type get_vbat_by_raw_data(){
		return raw_average_voltage_battery.output_value * DOUBLE_VBAT_SLOPE + DOUBLE_VBAT_OFFSET;
	}

	void update_raw_shunt_value(){
		raw_current_shunt = (double)ADC::get_value(shunt_id);
	}

	arithmetic_number_type get_shunt_by_raw_data(){
		return raw_current_shunt * DOUBLE_SHUNT_SLOPE + DOUBLE_SHUNT_OFFSET;
	}




	//#################  CURRENT CONTROL  #########################
	void PI_current_to_duty_cycle(){
		if(!flags.run_pi){
			return;
		}
		current_shunt = get_shunt_by_raw_data();
		if(current_shunt > 50.0 || current_shunt < -50.0){
			//send_to_fault();
		}
		Voltage_by_current_PI.input(desired_current - current_shunt);
		Voltage_by_current_PI.execute();
		change_pwms_duty(calculate_duty_by_voltage(Voltage_by_current_PI.output_value));
	}

	float calculate_duty_by_voltage(double voltage){
		if constexpr(running_mode == GUI_CONTROL){
			if(!flags.fixed_vbat){
				voltage_battery = get_vbat_by_raw_data();
			}
		}else{
			voltage_battery = get_vbat_by_raw_data();
		}

		if(voltage_battery < 0.0001){
			return 0;
		}
		if(voltage_battery > 252.5){
			voltage_battery = 252.5;
		}

		if(voltage > voltage_battery){
			return 100.0;
		}else if(voltage < -voltage_battery){
			return -100.0;
		}

		float duty = voltage * 100 / voltage_battery;

		if(duty < 0.5 && duty > -0.5){return 0;}

		return duty;
	}

	void shut_down(){
		change_pwms_duty(0);
		flags.run_pi = false;
		//flags.fixed_pwm = true;
	}
};

static LDU<RUNNING_MODE, ARITHMETIC_MODE> ldu_array[LDU_COUNT];
