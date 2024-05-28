#pragma once

#include "ST-LIB.hpp"
#include "LCU-SHARED.hpp"

/** #############################################################
 *  ###################  LCU_DESIGN_DATA  #######################
 *  #############################################################
 */

#define USING_1DOF (RUNNING_MODE == DOF1)
#define USING_5DOF (RUNNING_MODE != DOF1)
#define IS_HIL (RUNNING_MODE == DOF5_HIL)

static constexpr double MAXIMUM_DESIRED_CURRENT = 40.0;

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

inline void DOF5_update_airgap_data();
inline void DOF5_update_shunt_data();
inline void DOF5_update_vbat_data();
inline void DOF1_update_airgap_data();
inline void DOF1_update_shunt_data();
inline void DOF1_update_vbat_data();

inline void rise_current_PI_flag();
inline void rise_levitation_control_flag();
inline void rise_rise_housekeeping_tasks_flag();

inline void update_desired_current_LDU();
inline void run_current_PI();

inline void update_levitation_constants(float new_levitation_constants[LDU_COUNT][15]);
inline void start_levitation_control();
inline void set_desired_current_on_LDU();
inline void initial_order_callback();
inline void test_pwm_order_callback();

inline void send_to_fault();
inline void shutdown();

/* #################################################################
 * #####################  PINOUT DISTRIBUTION  #####################
 * #################################################################
 */
#define SPI_RS_PIN 		PD2

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

#define PWM_PIN_5_1		PD15
#define PWM_PIN_5_2		PD14
#define VBAT_PIN_5 		PF8
#define SHUNT_PIN_5 	PA2

#define PWM_PIN_6_1		PD12
#define PWM_PIN_6_2		PD13
#define VBAT_PIN_6 		PF7
#define SHUNT_PIN_6 	PA3

#define PWM_PIN_7_1		PB9
#define PWM_PIN_7_2		PB8
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

#define AIRGAP_PIN_1 	PA7
#define AIRGAP_PIN_2 	PA6
#define AIRGAP_PIN_3 	PA5
#define AIRGAP_PIN_4 	PA4
#define AIRGAP_PIN_5 	PB1
#define AIRGAP_PIN_6 	PB0
#define AIRGAP_PIN_7 	PC5
#define AIRGAP_PIN_8 	PC4

#define ON_BUFF_PIN_1 		PG7
#define ON_BUFF_PIN_2 		PG6
#define ON_BUFF_PIN_3 		PG5
#define ON_BUFF_PIN_4 		PG4
#define ON_BUFF_PIN_5 		PB2

