#pragma once

#include <CommonData/CommonData.hpp>

#define KP_CURRENT_TO_DUTY 10.0 //22.9546
#define KI_CURRENT_TO_DUTY 400.0 //208.3333
#define MOVING_AVERAGE_SIZE 20

template<LCU_running_modes running_mode, typename arithmetic_number_type>
class LDU{
public:
	uint8_t index = 0; /**< this index is the software index, and is one less than the hardware index, as this one starts with 0 and the hardware one starts in one */
	PWM *pwm1 = nullptr;
	PWM *pwm2 = nullptr;
	uint8_t vbat_id = 0;
	uint8_t shunt_id = 0;


	float desired_current = 0;
	float LDU_duty_cycle = 0;

	PI<IntegratorType::Trapezoidal> Voltage_by_current_PI;

	uint16_t binary_battery_voltage = 0;
	MovingAverageBlock<uint16_t, uint16_t, 10> binary_average_battery_voltage;
	float battery_voltage = 0.0;

	uint16_t binary_current_shunt = 0;
	float current_shunt = 0.0;


	struct LDU_flags{
		bool fixed_vbat = false;
		bool fixed_desired_current = false;
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
		shared_control_data.fixed_coil_current[index] = &binary_current_shunt;
		shared_control_data.fixed_battery_voltage[index] = &binary_battery_voltage;
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
			change_pwm1_duty((float)duty);
		}else{
			change_pwm1_duty(0);
			change_pwm2_duty((float)-duty);
		}
	}

	void set_pwms_duty(float duty){
		LDU_duty_cycle = duty;
		change_pwms_duty(duty);
	}

	void change_pwm1_freq(uint32_t freq){pwm1->set_frequency(freq);}
	void change_pwm2_freq(uint32_t freq){pwm2->set_frequency(freq);}


	//################  DATA STORING, PROCESSING AND PARSING  ###################
	void update_vbat_value(){
		binary_battery_voltage = ADC::get_int_value(vbat_id);
		binary_average_battery_voltage.compute(binary_battery_voltage);
	}

	float get_vbat_data(){
		return binary_average_battery_voltage.output_value * ADC_BINARY_TO_VOLTAGE * DOUBLE_VBAT_SLOPE + DOUBLE_VBAT_OFFSET;
	}

	void update_shunt_value(){
		binary_current_shunt = ADC::get_int_value(shunt_id);
	}

	float get_shunt_data(){
		return  binary_current_shunt * ADC_BINARY_TO_VOLTAGE * DOUBLE_SHUNT_SLOPE + DOUBLE_SHUNT_OFFSET;
	}




	//#################  CURRENT CONTROL  #########################
	void PI_current_to_duty_cycle(){
		current_shunt = get_shunt_data();
		if(!status_flags.enable_current_control){
			change_pwms_duty(LDU_duty_cycle);
			return;
		}
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
				battery_voltage = get_vbat_data();
			}
		}else{
			battery_voltage = get_vbat_data();
		}

		if(battery_voltage < 0.0001){
			return 0;
		}
		if(battery_voltage > 252.5){
			battery_voltage = 252.5;
		}

		if(voltage > battery_voltage){
			return 100.0;
		}else if(voltage < -battery_voltage){
			return -100.0;
		}

		float duty = voltage * 100 / battery_voltage;

		if(duty < 0.5 && duty > -0.5){return 0;}

		return duty;
	}
};

static LDU<RUNNING_MODE, ARITHMETIC_MODE> ldu_array[LDU_COUNT];
