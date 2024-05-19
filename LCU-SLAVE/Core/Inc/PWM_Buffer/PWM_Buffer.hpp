#pragma once

#include <CommonData/CommonData.hpp>

class PWM_Buffer{
public:
	uint8_t Buffers[5]{0};


	PWM_Buffer(){
#ifdef BOARD_PROTECTIONS //buffers will only be usable with protections enabled
		Buffers[0] = DigitalOutputService::inscribe(ON_BUFF_PIN_1);
		Buffers[1] = DigitalOutputService::inscribe(ON_BUFF_PIN_2);
		Buffers[2] = DigitalOutputService::inscribe(ON_BUFF_PIN_3);
		Buffers[3] = DigitalOutputService::inscribe(ON_BUFF_PIN_4);
		Buffers[4] = DigitalOutputService::inscribe(ON_BUFF_PIN_5);
#endif
		turn_off();
	}

	void turn_on(){
#ifdef BOARD_PROTECTIONS
		for(int i = 0; i < 5; i++){
			DigitalOutputService::turn_on(Buffers[i]);
		}
#endif
	}

	void turn_off(){
#ifdef BOARD_PROTECTIONS
		for(int i = 0; i < 5; i++){
			DigitalOutputService::turn_off(Buffers[i]);
		}
#endif
	}

	void turn_on_hems(){
#ifdef BOARD_PROTECTIONS
		for(int i = 0; i < 2; i++){
			DigitalOutputService::turn_on(Buffers[i]);
		}
#endif
	}

	void turn_on_ems(){
#ifdef BOARD_PROTECTIONS
		for(int i = 2; i < 5; i++){
			DigitalOutputService::turn_on(Buffers[i]);
		}
#endif
	}
};
