#pragma once

#include "Tools/Tools.hpp"
#include "SharedData.hpp"


static constexpr uint32_t ETH_PACKET_COUNT = 4;

static const uint16_t SEND_LCU_DATA_TCP_PACKET_ID = 315;
static constexpr uint16_t SEND_LCU_DATA_TCP_PACKET_INDEX = 0;

static const uint16_t SEND_LEVITATION_DATA_TCP_PACKET_ID = 316;
static constexpr uint16_t SEND_LEVITATION_DATA_TCP_PACKET_INDEX = 1;


static const uint16_t NOISE_DATA_TCP_PACKET_ID = 318;
static constexpr uint16_t NOISE_DATA_TCP_PACKET_INDEX = 2;

static constexpr uint16_t LPU_VOLTAGE_INTEGER_DATA_TCP_PACKET_ID = 981;
static constexpr uint16_t LPU_VOLTAGE_INTEGER_DATA_TCP_PACKET_INDEX = 3;



static constexpr uint32_t ETH_ORDER_COUNT = 13 *2; //duplicated for bypass versions
static constexpr uint16_t ETH_ORDER_BYPASS_ID_TO_ADD = 3000; //the ID of the real version plus this makes the ID of the bypass version
static constexpr uint16_t ETH_ORDER_BYPASS_INDEX_TO_ADD = ETH_ORDER_COUNT/2;

//############### VCU COMM ################

static constexpr uint16_t STABLE_LEVITATION_CONFIRMATION_TCP_ORDER_ID = 341;
static constexpr uint16_t STABLE_LEVITATION_CONFIRMATION_TCP_ORDER_INDEX = 0;

static constexpr uint16_t LANDING_COMPLETE_CONFIRMATION_TCP_ORDER_ID = 342;
static constexpr uint16_t LANDING_COMPLETE_CONFIRMATION_TCP_ORDER_INDEX = 1;

//############## TESTING ORDERS ###########
static constexpr uint32_t FIRST_ETH_TESTING_ORDER_INDEX = 3;

static constexpr uint16_t TEST_PWM_TCP_ORDER_ID = 350;
static constexpr uint16_t TEST_PWM_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX;

static constexpr uint16_t START_LEVITATION_CONTROL_TCP_ORDER_ID = 355;
static constexpr uint16_t START_LEVITATION_CONTROL_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+1;

static constexpr uint16_t TEST_DESIRED_CURRENT_TCP_ORDER_ID = 352;
static constexpr uint16_t TEST_DESIRED_CURRENT_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+2;

static constexpr uint16_t TEST_START_RESET_TCP_ORDER_ID = 353;
static constexpr uint16_t TEST_START_RESET_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+3;

static constexpr uint16_t TEST_STOP_RESET_TCP_ORDER_ID = 354;
static constexpr uint16_t TEST_STOP_RESET_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+4;


//######## IMPLEMENTING #########

static constexpr uint16_t START_VERTICAL_LEVITATION_TCP_ORDER_ID = 356;
static constexpr uint16_t START_VERTICAL_LEVITATION_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+5;

static constexpr uint16_t STOP_LEVITATION_TCP_ORDER_ID = 357;
static constexpr uint16_t STOP_LEVITATION_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+6;

static constexpr uint16_t STICK_DOWN_TCP_ORDER_ID = 358;
static constexpr uint16_t STICK_DOWN_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+7;

static constexpr uint16_t LANDING_TCP_ORDER_ID = 359;
static constexpr uint16_t LANDING_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+8;

static constexpr uint16_t START_HORIZONTAL_LEVITATION_TCP_ORDER_ID = 360;
static constexpr uint16_t START_HORIZONTAL_LEVITATION_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+9;

