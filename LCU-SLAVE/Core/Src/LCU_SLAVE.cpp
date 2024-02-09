#include "LCU_SLAVE.hpp"

LCU::LCU(){
	setup_configuration();
}

void LCU::update(){
	while(ErrorHandlerModel::error_triggered){
		ErrorHandlerModel::ErrorHandlerUpdate();
	}

	for(uint8_t i = 0; i < LDU_COUNT; i++){

		uint16_t vbat = LDU::ldu_array[i].get_vbat_value();
		uint16_t shunt = LDU::ldu_array[i].get_shunt_value();

		if(vbat > 32768){
			vbat = 0;
		}
		if(shunt > 32768){
			shunt = 0;
		}
	}
}


void LCU::setup_configuration(){
	//index is n but uses the n+1 hardware data, as hardware starts with 1 instead of 0.
	LDU::ldu_array[0] = LDU(0, PWM_PIN_1_1, PWM_PIN_1_2, VBAT_PIN_1, SHUNT_PIN_1);
	LDU::ldu_array[1] = LDU(1, PWM_PIN_2_1, PWM_PIN_2_2, VBAT_PIN_2, SHUNT_PIN_2);
	LDU::ldu_array[2] = LDU(2, PWM_PIN_3_1, PWM_PIN_3_2, VBAT_PIN_3, SHUNT_PIN_3);
	LDU::ldu_array[3] = LDU(3, PWM_PIN_4_1, PWM_PIN_4_2, VBAT_PIN_4, SHUNT_PIN_4);
	LDU::ldu_array[4] = LDU(4, PWM_PIN_5_1, PWM_PIN_5_2, VBAT_PIN_5, SHUNT_PIN_5);
	LDU::ldu_array[5] = LDU(5, PWM_PIN_6_1, PWM_PIN_6_2, VBAT_PIN_6, SHUNT_PIN_6);
	LDU::ldu_array[6] = LDU(6, PWM_PIN_7_1, PWM_PIN_7_2, VBAT_PIN_7, SHUNT_PIN_7);
	LDU::ldu_array[7] = LDU(7, PWM_PIN_8_1, PWM_PIN_8_2, VBAT_PIN_8, SHUNT_PIN_8);
	LDU::ldu_array[8] = LDU(8, PWM_PIN_9_1, PWM_PIN_9_2, VBAT_PIN_9, SHUNT_PIN_9);
	LDU::ldu_array[9] = LDU(9, PWM_PIN_10_1, PWM_PIN_10_2, VBAT_PIN_10, SHUNT_PIN_10);

	Airgaps::inscribe();
	Communication::init();
	STLIB::start();
	Communication::start();
	Airgaps::turn_on();

	for(uint8_t i = 0; i < LDU_COUNT; i++){
		LDU::ldu_array[i].start();
	}
}
