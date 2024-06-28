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

static constexpr float FLOAT_AIRGAP_SLOPE[AIRGAP_COUNT]{0.0101,0.0101,0.0101,0.0101,0.0068997,0.0108,0.0068997,0.0068997};
static constexpr float FLOAT_AIRGAP_OFFSET[AIRGAP_COUNT]{0.058182,0.058182,0.058182,0.058182,0.1308-0.00045,0.11652,0.1308-0.00045,0.1308-0.00045};

static constexpr uint32_t AIRGAP_UPDATE_DATA_HZ = 7500;
static constexpr float AIRGAP_UPDATE_PERIOD_SECONDS = (float) (1.0 / AIRGAP_UPDATE_DATA_HZ);
static constexpr uint32_t AIRGAP_MOVING_AVERAGE_COUNT = 10;

static constexpr float MAXIMUM_EXPECTED_AIRGAP_INCREASE = 0.00001;
static constexpr uint16_t MAXIMUM_EXPECTED_AIRGAP_INCREASE_BINARY[AIRGAP_COUNT]{
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[0]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[1]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[2]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[3]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[4]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[5]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[6]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)(MAXIMUM_EXPECTED_AIRGAP_INCREASE/(FLOAT_AIRGAP_SLOPE[7]*ADC_BINARY_TO_VOLTAGE)),
};

static constexpr float MINIMUM_EXPECTED_AIRGAP_VALUE = 0.068;

static constexpr uint16_t MINIMUM_EXPECTED_AIRGAP_VALUE_BINARY[AIRGAP_COUNT]{
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[0])/(FLOAT_AIRGAP_SLOPE[0]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[1])/(FLOAT_AIRGAP_SLOPE[1]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[2])/(FLOAT_AIRGAP_SLOPE[2]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[3])/(FLOAT_AIRGAP_SLOPE[3]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[4])/(FLOAT_AIRGAP_SLOPE[4]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[5])/(FLOAT_AIRGAP_SLOPE[5]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[6])/(FLOAT_AIRGAP_SLOPE[6]*ADC_BINARY_TO_VOLTAGE)),
		(uint16_t)((MINIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[7])/(FLOAT_AIRGAP_SLOPE[7]*ADC_BINARY_TO_VOLTAGE)),
};

static constexpr float MAXIMUM_EXPECTED_AIRGAP_VALUE = 0.087;

static constexpr uint16_t MAXIMUM_EXPECTED_AIRGAP_VALUE_BINARY[AIRGAP_COUNT]{
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[0])/(FLOAT_AIRGAP_SLOPE[0]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[1])/(FLOAT_AIRGAP_SLOPE[1]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[2])/(FLOAT_AIRGAP_SLOPE[2]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[3])/(FLOAT_AIRGAP_SLOPE[3]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[4])/(FLOAT_AIRGAP_SLOPE[4]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[5])/(FLOAT_AIRGAP_SLOPE[5]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[6])/(FLOAT_AIRGAP_SLOPE[6]*ADC_BINARY_TO_VOLTAGE)),
	(uint16_t)((MAXIMUM_EXPECTED_AIRGAP_VALUE  - FLOAT_AIRGAP_OFFSET[7])/(FLOAT_AIRGAP_SLOPE[7]*ADC_BINARY_TO_VOLTAGE)),
};
