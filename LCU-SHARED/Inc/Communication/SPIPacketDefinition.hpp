#pragma once

#include "Tools/Tools.hpp"
#include "SharedData.hpp"

static constexpr uint32_t SPI_ORDER_COUNT = 14;

static constexpr uint16_t MASTER_SLAVE_INITIAL_ORDER_ID = 15;
static constexpr uint16_t MASTER_SLAVE_INITIAL_ORDER_INDEX = 0;

static constexpr uint16_t SENSOR_DATA_ORDER_ID = 85;
static constexpr uint16_t SENSOR_DATA_ORDER_INDEX = 1;

static constexpr uint16_t LEVITATION_DATA_ORDER_ID = 86;
static constexpr uint16_t LEVITATION_DATA_ORDER_INDEX = 2;

static constexpr uint16_t START_LEVITATION_CONTROL_ORDER_ID = 100;
static constexpr uint16_t START_LEVITATION_CONTROL_ORDER_INDEX = 3;

static constexpr uint16_t START_HORIZONTAL_LEVITATION_ORDER_ID = 101;
static constexpr uint16_t START_HORIZONTAL_LEVITATION_ORDER_INDEX = 4;

static constexpr uint16_t STOP_LEVITATION_ORDER_ID = 102;
static constexpr uint16_t STOP_LEVITATION_ORDER_INDEX = 5;

static constexpr uint16_t ENTER_BOOSTER_ORDER_ID = 103;
static constexpr uint16_t ENTER_BOOSTER_ORDER_INDEX = 6;



static constexpr uint32_t FIRST_TESTING_ORDER_INDEX = 7;

static constexpr uint16_t TEST_PWM_ORDER_ID = 1001;
static constexpr uint16_t TEST_PWM_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX;

static constexpr uint16_t TEST_VBAT_ORDER_ID = 1002;
static constexpr uint16_t TEST_VBAT_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+1;

static constexpr uint16_t TEST_DESIRED_CURRENT_ORDER_ID = 1003;
static constexpr uint16_t TEST_DESIRED_CURRENT_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+2;

static constexpr uint16_t START_VERTICAL_LEVITATION_ORDER_ID = 1005;
static constexpr uint16_t START_VERTICAL_LEVITATION_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+3;

static constexpr uint16_t STABLE_LEVITATION_ORDER_ID = 1007;
static constexpr uint16_t STABLE_LEVITATION_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+4;

static constexpr uint16_t UNSTABLE_LEVITATION_ORDER_ID = 1008;
static constexpr uint16_t UNSTABLE_LEVITATION_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+5;

static constexpr uint16_t SEND_DISCHARGE_ORDER_ID = 1009;
static constexpr uint16_t SEND_DISCHARGE_ORDER_INDEX = FIRST_TESTING_ORDER_INDEX+6;

