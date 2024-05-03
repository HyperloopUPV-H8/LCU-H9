#pragma once

#include "Tools/Tools.hpp"


static constexpr double DOUBLE_VBAT_SLOPE = 180.29; //91.325
static constexpr double DOUBLE_VBAT_OFFSET = -18.524; //-9.3784

static constexpr uint32_t VBAT_UPDATE_DATA_HZ = 10;
static constexpr double VBAT_UPDATE_PERIOD_SECONDS = (double) (1.0 / VBAT_UPDATE_DATA_HZ);
