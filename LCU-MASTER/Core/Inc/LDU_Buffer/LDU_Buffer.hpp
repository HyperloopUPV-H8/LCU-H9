#pragma once

#include "CommonData/CommonData.hpp"

class LDU_Buffer{
public:
	static LDU_Buffer ldu_buffers[LDU_BUFFER_COUNT];

	uint8_t LDU_Fault_1_ID = 0;
	uint8_t LDU_Ready_1_ID = 0;
	uint8_t LDU_Fault_2_ID = 0;
	uint8_t LDU_Ready_2_ID = 0;
	DigitalOutput reset;

	bool shut_down = false;
	bool fixed_reset = false;
	bool fixed_reset_value = false;

	LDU_Buffer() = default;

	LDU_Buffer(Pin &reset_pin, Pin &fault_1_pin, Pin &ready_1_pin, Pin &fault_2_pin, Pin &ready_2_pin) : reset{reset_pin}{
		LDU_Fault_1_ID = DigitalInput::inscribe(fault_1_pin);
		LDU_Ready_1_ID = DigitalInput::inscribe(ready_1_pin);
		LDU_Fault_2_ID = DigitalInput::inscribe(fault_2_pin);
		LDU_Ready_2_ID = DigitalInput::inscribe(ready_2_pin);
	}

	bool check_ready_and_fault(){
		return 	DigitalInput::read_pin_state(LDU_Fault_1_ID) == PinState::ON &&
				DigitalInput::read_pin_state(LDU_Fault_2_ID) == PinState::ON &&
				DigitalInput::read_pin_state(LDU_Ready_1_ID) == PinState::ON &&
				DigitalInput::read_pin_state(LDU_Ready_2_ID) == PinState::ON;
	}

	void update(){
if constexpr(IS_HIL){
		reset.turn_off();
		return;
}
		if(shut_down){
			reset.turn_off();
		}else{
			if((fixed_reset && fixed_reset_value) || (!fixed_reset && check_ready_and_fault())){
				reset.turn_on();
			}else{
				reset.turn_off();
			}
		}
	}

	static void update_buffers(){
		for(int i = 0; i < LDU_BUFFER_COUNT; i++){
			ldu_buffers[i].update();
		}
	}

	static void shutdown_buffers(){
		for(int i = 0; i < LDU_BUFFER_COUNT; i++){
			ldu_buffers[i].shut_down = true;
		}
	}
};
