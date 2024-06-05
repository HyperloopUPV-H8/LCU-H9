#pragma once

#include "Tools/Tools.hpp"


//
//
static constexpr float FLOAT_SHUNT_SLOPE_HIL = -34.3;
static constexpr float FLOAT_SHUNT_OFFSET_HIL = 67.1;

static constexpr double FLOAT_SHUNT_SLOPE[LDU_COUNT] = {-82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125, -82.32*1.1125};
static constexpr double FLOAT_SHUNT_OFFSET[LDU_COUNT] = {196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125, 196.7*1.1125};


static constexpr uint32_t CURRENT_UPDATE_DATA_HZ = 10000;
static constexpr double CURRENT_UPDATE_PERIOD_SECONDS = (double) (1.0 / CURRENT_UPDATE_DATA_HZ);
static constexpr uint32_t CURRENT_MOVING_AVERAGE_SIZE = 10;


static constexpr uint32_t CURRENT_ZEROING_SAMPLING_FREQUENCY_HZ = (400);
static constexpr double CURRENT_ZEROING_SAMPLING_PERIOD_SECONDS = (double) (1.0 / CURRENT_ZEROING_SAMPLING_FREQUENCY_HZ);
static constexpr uint32_t CURRENT_ZEROING_SAMPLE_AMOUNT = 1000;
