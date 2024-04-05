#pragma once

#include "ST-LIB.hpp"
#include "LCU-SHARED.hpp"

/** #############################################################
 *  ###################  LCU_DESIGN_DATA  #######################
 *  #############################################################
 */
static constexpr uint32_t CURRENT_UPDATE_DATA_HZ = 10000;
static constexpr double CURRENT_UPDATE_PERIOD_SECONDS = (double) (1.0 / CURRENT_UPDATE_DATA_HZ);


static constexpr double MAXIMUM_DESIRED_CURRENT = 45.0;

/*  #############################################################
 *  ################### LCU_RUNNING_MODE  #######################
 *  #############################################################
 */
/*
enum LCU_running_modes{
	GUI_CONTROL,
	DOF1,
};

#define RUNNING_MODE GUI_CONTROL
#define ARITHMETIC_MODE double
*/
#define DOF1_USED_LDU_INDEX 9
#define DOF1_USED_AIRGAP_INDEX 0

/*  ##############################################################
 *  ###################  SHARED_CONTROL_DATA  ####################
 *  ##############################################################
 */

static struct periph_pointers{
	PWM* ldu_pwms[LDU_COUNT][2];

}slave_periph_pointers;

/*  #################################################################
 *  ################  STATIC FUNCTIONS DECLARATION  #################
 *  #################################################################
 */

inline void update_airgap_data();
static void update_shunt_data();
static void update_vbat_data();

void rise_current_PI_flag();
void rise_levitation_control_flag();
static void rise_rise_housekeeping_tasks_flag();

static void run_current_PI();

static void set_vbat_on_LDU();
static void set_desired_current_on_LDU();
static void test_pwm_order_callback();

void send_to_fault();
void shut_down();

/* #################################################################
 * #####################  PINOUT DISTRIBUTION  #####################
 * #################################################################
 */
#define SPI_RS_PIN 		PE0

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

#define PWM_PIN_6_1		PE9 //PD12 on board
#define PWM_PIN_6_2		PE11 //PD13 on board
#define VBAT_PIN_6 		PF7
#define SHUNT_PIN_6 	PF11 //PA3 on board

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

#define PWM_PIN_10_1	PD12 //PE9 on board
#define PWM_PIN_10_2	PD13 //PE11 on board
#define VBAT_PIN_10 	PC2
#define SHUNT_PIN_10 	PA3 //PF11 on board

#define AIRGAP_PIN_1 	PA4 //PA7 on board
#define AIRGAP_PIN_2 	PA6
#define AIRGAP_PIN_3 	PA5
#define AIRGAP_PIN_4 	PA7 //PA4 on board
#define AIRGAP_PIN_5 	PB1
#define AIRGAP_PIN_6 	PB0
#define AIRGAP_PIN_7 	PC5
#define AIRGAP_PIN_8 	PC4
