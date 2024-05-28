#pragma once

#include <CommonData/CommonData.hpp>

class PWM_Buffer{
public:
	uint8_t Buffers[5]{0};


	PWM_Buffer(){
if constexpr(!IS_HIL){
		Buffers[0] = DigitalOutputService::inscribe(ON_BUFF_PIN_1);
		Buffers[1] = DigitalOutputService::inscribe(ON_BUFF_PIN_2);
		Buffers[2] = DigitalOutputService::inscribe(ON_BUFF_PIN_3);
		Buffers[3] = DigitalOutputService::inscribe(ON_BUFF_PIN_4);
		Buffers[4] = DigitalOutputService::inscribe(ON_BUFF_PIN_5);
}
		turn_on(); //buffers are active on low
	}

	void turn_on(){
if constexpr(!IS_HIL){
		for(int i = 0; i < 5; i++){
			DigitalOutputService::turn_off(Buffers[i]);
		}
}
	}

	void turn_off(){
if constexpr(!IS_HIL){
		for(int i = 0; i < 5; i++){
			DigitalOutputService::turn_on(Buffers[i]);
		}
}
	}

	void turn_on_hems(){
if constexpr(!IS_HIL){
		for(int i = 0; i < 2; i++){
			DigitalOutputService::turn_off(Buffers[i]);
		}
}
	}

	void turn_on_ems(){
if constexpr(!IS_HIL){
		for(int i = 2; i < 5; i++){
			DigitalOutputService::turn_off(Buffers[i]);
		}
}
	}
};
