#pragma once

#include "Tools/Tools.hpp"

static constexpr float FLOAT_1DOF_AIRGAP_SLOPE =  7.8112/1000;
static constexpr float FLOAT_1DOF_AIRGAP_OFFSET = 3.0947/1000;

static constexpr float FLOAT_HEMS_HIL_AIRGAP_SLOPE = 0.018/3.3;
static constexpr float FLOAT_HEMS_HIL_AIRGAP_OFFSET = 0.07;

static constexpr float FLOAT_EMS_HIL_AIRGAP_SLOPE = 0.03/3.3;
static constexpr float FLOAT_EMS_HIL_AIRGAP_OFFSET = 0.120;

static constexpr float FLOAT_HEMS_AIRGAP_SLOPE =  0.0101; //mm/mv
static constexpr float FLOAT_HEMS_AIRGAP_OFFSET = 58.182/1000; //mm

static constexpr float FLOAT_EMS_AIRGAP_SLOPE =  13.595/1000; //mm/v
static constexpr float FLOAT_EMS_AIRGAP_OFFSET = 108.42/1000; //mm

static constexpr float FLOAT_AIRGAP_SLOPE[AIRGAP_COUNT]{0.0101,0.0101,0.0101,0.0101,0.0068997,0.011159,0.0068997,0.0068997};
static constexpr float FLOAT_AIRGAP_OFFSET[AIRGAP_COUNT]{0.058182,0.058182,0.058182,0.058182,0.1308-0.00045,0.11679-0.00065,0.1308-0.00045,0.1308-0.00045};

static constexpr uint32_t AIRGAP_UPDATE_DATA_HZ = 7500;
static constexpr float AIRGAP_UPDATE_PERIOD_SECONDS = (float) (1.0 / AIRGAP_UPDATE_DATA_HZ);
static constexpr uint32_t AIRGAP_MOVING_AVERAGE_COUNT = 10;
