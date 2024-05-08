#pragma once

#include "Tools/Tools.hpp"


static constexpr double FLOAT_SHUNT_SLOPE = -34.3;
static constexpr double FLOAT_SHUNT_OFFSET = 67.1;


static constexpr uint32_t CURRENT_UPDATE_DATA_HZ = 2000;
static constexpr double CURRENT_UPDATE_PERIOD_SECONDS = (double) (1.0 / CURRENT_UPDATE_DATA_HZ);
static constexpr uint32_t CURRENT_MOVING_AVERAGE_SIZE = 20;
