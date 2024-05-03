#pragma once

#include "Tools/Tools.hpp"
#include "SharedData.hpp"


static constexpr uint32_t ETH_PACKET_COUNT = 2;

static const uint16_t SEND_LPU_TEMPERATURES_TCP_PACKET_ID = 314;
static constexpr uint16_t SEND_LPU_TEMPERATURES_TCP_PACKET_INDEX = 0;

static const uint16_t SEND_LCU_DATA_TCP_PACKET_ID = 315;
static constexpr uint16_t SEND_LCU_DATA_TCP_PACKET_INDEX = 1;



static constexpr uint32_t ETH_ORDER_COUNT = 6;

static constexpr uint32_t FIRST_ETH_TESTING_ORDER_INDEX = 1;

static const uint16_t TEST_PWM_TCP_ORDER_ID = 350;
static constexpr uint16_t TEST_PWM_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX;

static const uint16_t START_LEVITATION_CONTROL_TCP_ORDER_ID = 355;
static constexpr uint16_t START_LEVITATION_CONTROL_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+1;

static const uint16_t TEST_DESIRED_CURRENT_TCP_ORDER_ID = 352;
static constexpr uint16_t TEST_DESIRED_CURRENT_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+2;

static const uint16_t TEST_START_RESET_TCP_ORDER_ID = 353;
static constexpr uint16_t TEST_START_RESET_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+3;

static const uint16_t TEST_STOP_RESET_TCP_ORDER_ID = 354;
static constexpr uint16_t TEST_STOP_RESET_TCP_ORDER_INDEX = FIRST_ETH_TESTING_ORDER_INDEX+4;
