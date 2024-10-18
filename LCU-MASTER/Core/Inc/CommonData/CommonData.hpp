#pragma once

#include "ST-LIB.hpp"
#include "LCU-SHARED.hpp"
#include "CommonCData.h"

/** #############################################################
 *  ###################  LCU_MASTER_SHARED  #######################
 *  #############################################################
 */

#define VCU_PRESENT 1
#define USING_1DOF 0
#define USING_5DOF 1
#define IS_HIL (RUNNING_MODE == DOF5_HIL)
#define POD_PROTECTIONS (RUNNING_MODE == POD)

static ip_addr_t master_ip_addr = IPADDR4_INIT_BYTES(LCU_IP_B0,LCU_IP_B1,LCU_IP_B2,LCU_IP_B3);
static IPV4 LCU_IP(master_ip_addr);
static IPV4 VCU_IP("192.168.1.3");
static IPV4 BACKEND("192.168.0.9");


static const uint32_t TCP_SERVER_PORT = 50500;
static const uint32_t TCP_CLIENT_PORT = 50401;
static const uint32_t TCP_VCU_PORT = 50304;
static const uint32_t UDP_VCU_PORT = 50414;
static const uint32_t UDP_PORT = 50400;

extern control_data shared_control_data;

struct pod_data{
	uint16_t integer_lpu_voltage[LDU_COUNT]{0};
	uint16_t average_integer_lpu_voltage = 0;
	bool useless = false;
};
extern pod_data shared_pod_data;

/*  #################################################################
 *  ################  STATIC FUNCTIONS DECLARATION  #################
 *  #################################################################
 */

void fix_buffer_reset_high();
void fix_buffer_reset_low();
void define_shared_data();
void general_enter_operational();
void general_enter_fault();
void levitation_enter_idle();
void external_enter_discharging();
void levitation_enter_discharging();

void initial_order_callback();

/* #################################################################
 * #####################  PINOUT DISTRIBUTION  #####################
 * #################################################################
 */

#define SPI_RS_PIN PB2

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

#define LCU_BUFFER_RESET_PIN_5 	PB14
#define LCU_BUFFER_FAULT_PIN_9 	PE14
#define LCU_BUFFER_READY_PIN_9 	PE13
#define LCU_BUFFER_FAULT_PIN_10 PE11
#define LCU_BUFFER_READY_PIN_10 PE10


#define OPERATIONAL_LED_PIN 	PG8
#define FAULT_LED_PIN			PG7
#define CAN_LED_PIN				PG6
#define FLASH_LED_PIN			PG5
#define SLEEP_LED_PIN			PG4
