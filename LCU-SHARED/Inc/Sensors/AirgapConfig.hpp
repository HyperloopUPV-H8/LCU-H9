#pragma once

#include "Tools/Tools.hpp"

static constexpr double DOUBLE_AIRGAP_SLOPE =  7.8112/1000;
static constexpr double DOUBLE_AIRGAP_OFFSET = 3.0947/1000;

#define DOUBLE_VBAT_SLOPE 180.29 //91.325
#define DOUBLE_VBAT_OFFSET -18.524 //-9.3784

#define DOUBLE_SHUNT_SLOPE -34.3
#define DOUBLE_SHUNT_OFFSET 67.1

static constexpr uint32_t AIRGAP_UPDATE_DATA_HZ = 7500;
static constexpr double AIRGAP_UPDATE_PERIOD_SECONDS = (double) (1.0 / AIRGAP_UPDATE_DATA_HZ);
static constexpr uint32_t AIRGAP_MOVING_AVERAGE_COUNT = 10;
