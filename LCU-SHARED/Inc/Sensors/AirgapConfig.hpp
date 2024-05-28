#pragma once

#include "Tools/Tools.hpp"

static constexpr float FLOAT_1DOF_AIRGAP_SLOPE =  7.8112/1000;
static constexpr float FLOAT_1DOF_AIRGAP_OFFSET = 3.0947/1000;

static constexpr float FLOAT_HEMS_AIRGAP_SLOPE =  0.018/3.3; //temporal profile of the sensor for HIL purposes
static constexpr float FLOAT_HEMS_AIRGAP_OFFSET = 0.07;

static constexpr float FLOAT_EMS_AIRGAP_SLOPE =  0.03/3.3; //temporal profile of the sensor for HIL purposes
static constexpr float FLOAT_EMS_AIRGAP_OFFSET = 0.120;

static constexpr uint32_t AIRGAP_UPDATE_DATA_HZ = 3750;
static constexpr float AIRGAP_UPDATE_PERIOD_SECONDS = (float) (1.0 / AIRGAP_UPDATE_DATA_HZ);
static constexpr uint32_t AIRGAP_MOVING_AVERAGE_COUNT = 10;
