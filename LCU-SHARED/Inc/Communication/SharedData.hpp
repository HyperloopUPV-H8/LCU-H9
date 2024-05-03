#pragma once

#include "Tools/Tools.hpp"
#include "Layout/Layout.hpp"

static struct control_data{
	uint8_t master_status = 0;
	uint8_t slave_status = 0;

	uint16_t fixed_coil_temperature[LDU_COUNT]{0};
	uint16_t fixed_lpu_temperature[LDU_COUNT]{0};
	uint16_t *fixed_coil_current[LDU_COUNT]{nullptr};
	uint16_t *fixed_battery_voltage[LDU_COUNT]{nullptr};
	uint16_t *fixed_airgap_distance[AIRGAP_COUNT]{nullptr};


	float float_coil_temperature[LDU_COUNT]{0};
	float float_lpu_temperature[LDU_COUNT]{0};
	float *float_coil_current[LDU_COUNT]{nullptr};
	float *float_battery_voltage[LDU_COUNT]{nullptr};
	float *float_airgap_distance[AIRGAP_COUNT]{nullptr};
}shared_control_data;
