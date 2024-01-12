#include "LCU_SLAVE.hpp"

LCU::LCU(){
	ldu_array[0] = LDU(PWM_PIN_1_1, PWM_PIN_1_2, VBAT_PIN_1, SHUNT_PIN_1);
	ldu_array[1] = LDU(PWM_PIN_2_1, PWM_PIN_2_2, VBAT_PIN_2, SHUNT_PIN_2);
	ldu_array[2] = LDU(PWM_PIN_3_1, PWM_PIN_3_2, VBAT_PIN_3, SHUNT_PIN_3);
	ldu_array[3] = LDU(PWM_PIN_4_1, PWM_PIN_4_2, VBAT_PIN_4, SHUNT_PIN_4);
	ldu_array[4] = LDU(PWM_PIN_5_1, PWM_PIN_5_2, VBAT_PIN_5, SHUNT_PIN_5);
	ldu_array[5] = LDU(PWM_PIN_6_1, PWM_PIN_6_2, VBAT_PIN_6, SHUNT_PIN_6);
	ldu_array[6] = LDU(PWM_PIN_7_1, PWM_PIN_7_2, VBAT_PIN_7, SHUNT_PIN_7);
	ldu_array[7] = LDU(PWM_PIN_8_1, PWM_PIN_8_2, VBAT_PIN_8, SHUNT_PIN_8);
	ldu_array[8] = LDU(PWM_PIN_9_1, PWM_PIN_9_2, VBAT_PIN_9, SHUNT_PIN_9);
	ldu_array[9] = LDU(PWM_PIN_10_1, PWM_PIN_10_2, VBAT_PIN_10, SHUNT_PIN_10);

	STLIB::start();

	communication.start();
	for(uint8_t i = 0; i < CommonData::LDU_COUNT; i++){
		ldu_array[i].start();
	}
}

void LCU::update(){
	while(ErrorHandlerModel::error_triggered){
		ErrorHandlerModel::ErrorHandlerUpdate();
	}

	SPIPacket  *packet_pointer;
	for(uint8_t i = 0; i < CommonData::LDU_COUNT; i++){
		packet_pointer = SPIPacket::SPIPacketsByID[CommonData::TEST_PWM_1_PACKET_ID+i*2];

		ldu_array[i].change_pwm1_duty(std::bit_cast<float>(* ((uint32_t*) &packet_pointer->master_data[CommonData::TEST_PWM_PACKET_DUTY_BYTE])));

		packet_pointer = SPIPacket::SPIPacketsByID[CommonData::TEST_PWM_1_PACKET_ID+1+i*2];

		ldu_array[i].change_pwm2_duty(std::bit_cast<float>(* ((uint32_t*) &packet_pointer->master_data[CommonData::TEST_PWM_PACKET_DUTY_BYTE])));

		uint16_t value = ldu_array[i].get_vbat_value();
		ldu_array[i].get_shunt_value();
	}
}
