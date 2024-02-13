#pragma once

#include "ST-LIB.hpp"
#include "CommonCData.h"

static const uint8_t LDU_COUNT = 10;
static const uint8_t AIRGAP_COUNT = 8;

static ip_addr_t master_ip_addr = IPADDR4_INIT_BYTES(MASTER_IP_B0,MASTER_IP_B1,MASTER_IP_B2,MASTER_IP_B3);
static IPV4 MASTER_IP(master_ip_addr);
static IPV4 BACKEND("192.168.0.9");
static const uint32_t TCP_SERVER_PORT = 50500;
static const uint32_t TCP_CLIENT_PORT = 50401;
static const uint32_t UDP_PORT = 50400;


static struct control_data{
	uint8_t master_status = 0;
	uint8_t slave_status = 0;

	uint16_t fixed_coil_temperature[LDU_COUNT]{0};
	uint16_t fixed_lpu_temperature[LDU_COUNT]{0};
	uint16_t fixed_coil_current[LDU_COUNT]{0};
	uint16_t fixed_battery_voltage[LDU_COUNT]{0};
	uint16_t fixed_airgap_distance[AIRGAP_COUNT]{0};


	float coil_temperature[LDU_COUNT]{0.0};
	float lpu_temperature[LDU_COUNT]{0.0};
	float coil_current[LDU_COUNT]{0.0};
	float battery_voltage[LDU_COUNT]{0.0};
	float airgap_distance[AIRGAP_COUNT]{0.0};
}master_control_data;


static constexpr uint32_t ETH_ORDER_COUNT = 2;

static constexpr uint16_t ETH_REFRESH_DATA_PERIOD_MS = 100;

static const uint16_t TEST_PWM_TCP_ORDER_ID = 350;
static constexpr uint16_t TEST_PWM_TCP_ORDER_INDEX = 0;
static const uint16_t SEND_LPU_TEMPERATURES_TCP_ORDER_ID = 314;
static constexpr uint16_t SEND_LPU_TEMPERATURES_TCP_ORDER_INDEX = 1;


static constexpr uint32_t SPI_ORDER_COUNT = 2;

static const uint16_t TEST_PWM_PACKET_ID = 1001;
static constexpr uint16_t TEST_PWM_ORDER_INDEX = 0;
static const uint16_t MASTER_SLAVE_DATA_ORDER_ID = 27;
static constexpr uint16_t MASTER_SLAVE_DATA_ORDER_INDEX = 1;



#define COIL_T_PIN_1	PC3
#define LPU_T_PIN_1 	PA4

#define COIL_T_PIN_2	PA0
#define LPU_T_PIN_2 	PA3

#define COIL_T_PIN_3	PC2
#define LPU_T_PIN_3 	PA5

#define COIL_T_PIN_4	PC0
#define LPU_T_PIN_4 	PB1

#define COIL_T_PIN_5	PF6
#define LPU_T_PIN_5 	PB0

#define COIL_T_PIN_6	PF7
#define LPU_T_PIN_6 	PA6

#define COIL_T_PIN_7	PF5
#define LPU_T_PIN_7 	PF11

#define COIL_T_PIN_8	PF10
#define LPU_T_PIN_8 	PF14

#define COIL_T_PIN_9	PF9
#define LPU_T_PIN_9 	PF13

#define COIL_T_PIN_10	PF8
#define LPU_T_PIN_10 	PF12
