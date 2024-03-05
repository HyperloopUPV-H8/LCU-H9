#pragma once

#include "ST-LIB.hpp"
#include "LCU-SHARED.hpp"
#include "CommonCData.h"

/** #############################################################
 *  ###################  LCU_DESIGN_DATA  #######################
 *  #############################################################
 */

//static constexpr uint8_t LDU_COUNT = 10;
static constexpr uint8_t LDU_BUFFER_COUNT = LDU_COUNT/2;
static constexpr uint8_t AIRGAP_COUNT = 8;

static constexpr uint16_t ETH_REFRESH_DATA_PERIOD_MS = 100;
static constexpr uint16_t SPI_REFRESH_DATA_PERIOD_MS = 10;

static ip_addr_t master_ip_addr = IPADDR4_INIT_BYTES(MASTER_IP_B0,MASTER_IP_B1,MASTER_IP_B2,MASTER_IP_B3);
static IPV4 MASTER_IP(master_ip_addr);
static IPV4 BACKEND("192.168.0.9");
static const uint32_t TCP_SERVER_PORT = 50500;
static const uint32_t TCP_CLIENT_PORT = 50401;
static const uint32_t UDP_PORT = 50400;


/*  #############################################################
 *  ################### LCU_RUNNING_MODE  #######################
 *  #############################################################
 */

enum LCU_running_modes{
	GUI_CONTROL,
	DOF1,
};

#define RUNNING_MODE GUI_CONTROL
#define ARITHMETIC_MODE double


/*  ##############################################################
 *  ###################  SHARED_CONTROL_DATA  ####################
 *  ##############################################################
 */

enum LCU_states{
	INITIAL = 0,
	OPERATIONAL,
	FAULT,
};

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


/*  #################################################################
 *  ################  ETHERNET PACKET STRUCTURE  ####################
 *  #################################################################
 */

static constexpr uint32_t ETH_PACKET_COUNT = 1;

static const uint16_t SEND_LPU_TEMPERATURES_TCP_PACKET_ID = 314;
static constexpr uint16_t SEND_LPU_TEMPERATURES_TCP_PACKET_INDEX = 0;



static constexpr uint32_t ETH_ORDER_COUNT = 6;

static constexpr uint32_t FIRST_ETH_TESTING_ORDER_INDEX = 1;

static const uint16_t TEST_PWM_TCP_ORDER_ID = 350;
static constexpr uint16_t TEST_PWM_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX;

static const uint16_t TEST_VBAT_TCP_ORDER_ID = 351;
static constexpr uint16_t TEST_VBAT_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+1;

static const uint16_t TEST_DESIRED_CURRENT_TCP_ORDER_ID = 352;
static constexpr uint16_t TEST_DESIRED_CURRENT_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+2;

static const uint16_t TEST_START_RESET_TCP_ORDER_ID = 353;
static constexpr uint16_t TEST_START_RESET_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+3;

static const uint16_t TEST_STOP_RESET_TCP_ORDER_ID = 354;
static constexpr uint16_t TEST_STOP_RESET_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+4;



/*  #################################################################
 *  #######################  PACKET STRUCTURE  ######################
 *  #################################################################
 */

static constexpr uint32_t SPI_ORDER_COUNT = 5;

static constexpr uint16_t MASTER_SLAVE_INITIAL_ORDER_ID = 15;
static constexpr uint16_t MASTER_SLAVE_INITIAL_ORDER_INDEX = 0;

static constexpr uint16_t MASTER_SLAVE_DATA_ORDER_ID = 27;
static constexpr uint16_t MASTER_SLAVE_DATA_ORDER_INDEX = 1;


static constexpr uint32_t FIRST_TESTING_ORDER_INDEX = 2;

static constexpr uint16_t TEST_PWM_ORDER_ID = 1001;
static constexpr uint16_t TEST_PWM_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX;
static constexpr uint16_t TEST_VBAT_ORDER_ID = 1002;
static constexpr uint16_t TEST_VBAT_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+1;
static constexpr uint16_t TEST_DESIRED_CURRENT_ORDER_ID = 1003;
static constexpr uint16_t TEST_DESIRED_CURRENT_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+2;

/*  #################################################################
 *  ################  STATIC FUNCTIONS DECLARATION  #################
 *  #################################################################
 */

void fix_buffer_reset_high();
void fix_buffer_reset_low();

/* #################################################################
 * #####################  PINOUT DISTRIBUTION  #####################
 * #################################################################
 */

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

#define LCU_BUFFER_RESET_PIN_1 PD9
#define LCU_BUFFER_FAULT_PIN_1 PE9
#define LCU_BUFFER_READY_PIN_1 PE8
#define LCU_BUFFER_FAULT_PIN_2 PE7
#define LCU_BUFFER_READY_PIN_2 PG1

#define LCU_BUFFER_RESET_PIN_2 PD10
#define LCU_BUFFER_FAULT_PIN_3 PF2
#define LCU_BUFFER_READY_PIN_3 PF1
#define LCU_BUFFER_FAULT_PIN_4 PE6
#define LCU_BUFFER_READY_PIN_4 PE5

#define LCU_BUFFER_RESET_PIN_3 PD8
#define LCU_BUFFER_FAULT_PIN_5 PE4
#define LCU_BUFFER_READY_PIN_5 PE3
#define LCU_BUFFER_FAULT_PIN_6 PC8
#define LCU_BUFFER_READY_PIN_6 PC7

#define LCU_BUFFER_RESET_PIN_4 PB15
#define LCU_BUFFER_FAULT_PIN_7 PD15
#define LCU_BUFFER_READY_PIN_7 PD14
#define LCU_BUFFER_FAULT_PIN_8 PB10
#define LCU_BUFFER_READY_PIN_8 PB11

#define LCU_BUFFER_RESET_PIN_5 PB14
#define LCU_BUFFER_FAULT_PIN_9 PE14
#define LCU_BUFFER_READY_PIN_9 PE13
#define LCU_BUFFER_FAULT_PIN_10 PE11
#define LCU_BUFFER_READY_PIN_10 PE10

