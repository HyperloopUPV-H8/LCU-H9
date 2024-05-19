#pragma once

#include <CommonData/CommonData.hpp>

class PWM_Buffer{
	uint8_t Buffers[5];


	PWM_Buffer(){
		Buffers[0] = DigitalOutputService::inscribe(ON_BUFF_PIN_1);
		Buffers[1] = DigitalOutputService::inscribe(ON_BUFF_PIN_2);
		Buffers[2] = DigitalOutputService::inscribe(ON_BUFF_PIN_3);
		Buffers[3] = DigitalOutputService::inscribe(ON_BUFF_PIN_4);
		Buffers[4] = DigitalOutputService::inscribe(ON_BUFF_PIN_5);
		turn_off();
	}

	void turn_on(){
		for(int i = 0; i < 5; i++){
			Buffers[i].turn_on();
		}
	}

	void turn_off(){
		for(int i = 0; i < 5; i++){
			Buffers[i].turn_off();
		}
	}

	void turn_on_hems(){
		for(int i = 0; i < 2; i++){
			Buffers[i].turn_off();
		}
	}
};
