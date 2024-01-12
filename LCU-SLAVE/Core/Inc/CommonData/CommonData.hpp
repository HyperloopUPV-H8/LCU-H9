#pragma once

#include "ST-LIB.hpp"

class CommonData{
public:
	static constexpr uint8_t LDU_COUNT = 10;
	static constexpr uint32_t PWM_FREQ_HZ = 1000;

	static constexpr uint16_t TEST_PWM_1_PACKET_ID = 1001;
	static constexpr uint16_t TEST_PWM_PACKET_AMOUNT = LDU_COUNT*2;
	static constexpr uint8_t TEST_PWM_PACKET_DUTY_BYTE = 2;
	static constexpr uint8_t TEST_PWM_PACKET_MASTER_SIZE = 4;
	static constexpr uint8_t TEST_PWM_PACKET_SLAVE_SIZE = 4;

};


#define PWM_PIN_1_1 	PE5
#define PWM_PIN_1_2 	PE6
#define VBAT_PIN_1 		PF3
#define SHUNT_PIN_1 	PC1

#define PWM_PIN_2_1		PB4
#define PWM_PIN_2_2		PB5
#define VBAT_PIN_2 		PF4
#define SHUNT_PIN_2 	PC0

#define PWM_PIN_3_1		PC8
#define PWM_PIN_3_2		PC9
#define VBAT_PIN_3 		PF5
#define SHUNT_PIN_3 	PA0

#define PWM_PIN_4_1		PC6
#define PWM_PIN_4_2		PC7
#define VBAT_PIN_4 		PF6
#define SHUNT_PIN_4 	PA1

#define PWM_PIN_5_1		PD14
#define PWM_PIN_5_2		PD15
#define VBAT_PIN_5 		PF8
#define SHUNT_PIN_5 	PA2

#define PWM_PIN_6_1		PD12
#define PWM_PIN_6_2		PD13
#define VBAT_PIN_6 		PF7
#define SHUNT_PIN_6 	PA3

#define PWM_PIN_7_1		PB11
#define PWM_PIN_7_2		PB10
#define VBAT_PIN_7 		PF10
#define SHUNT_PIN_7 	PF14

#define PWM_PIN_8_1		PB14
#define PWM_PIN_8_2		PB15
#define VBAT_PIN_8 		PF9
#define SHUNT_PIN_8 	PF13

#define PWM_PIN_9_1		PE13
#define PWM_PIN_9_2		PE14
#define VBAT_PIN_9 		PC3
#define SHUNT_PIN_9 	PF12

#define PWM_PIN_10_1	PE9
#define PWM_PIN_10_2	PE11
#define VBAT_PIN_10 	PC2
#define SHUNT_PIN_10 	PF11
