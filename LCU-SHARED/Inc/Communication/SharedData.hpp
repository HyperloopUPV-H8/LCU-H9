#pragma once

#include "Tools/Tools.hpp"
#include "Layout/Layout.hpp"


struct control_flags{
	bool enable_levitation_control = false;
	bool enable_lateral_levitation_control = false;
	bool enable_automatic_lateral_levitation_transition = false;
	bool enable_nominal_control = false;
	bool landing_flag = false;
	bool fault_flag = false;
	bool testing_flag = false;
};

struct control_data{
	control_flags flags{};

	uint8_t *master_status = nullptr;
	uint8_t *master_secondary_status = nullptr; //does nothing for now
	uint8_t *master_running_mode = nullptr; //running mode code on INITIAL
	uint8_t *slave_status = nullptr;
	uint8_t *slave_secondary_status = nullptr; //contains flags on INITIAL, levitation state machine on OPERATIONAL, and TODO: error code on FAULT
	uint8_t *slave_running_mode = nullptr; //running mode code on INITIAL


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
	float *shunt_zeroing_offset[LDU_COUNT]{nullptr};

	uint32_t *current_control_count = nullptr;
	uint32_t *levitation_control_count = nullptr;

	float *float_current_ref[LDU_COUNT]{nullptr};
	float *float_airgap_to_pos[5]{nullptr};
	float *float_airgap_to_pos_der[5]{nullptr};
	float *float_airgap_to_pos_in[5]{nullptr};
};

static uint16_t ldu_to_change = 0;
static float duty_to_change = 0;
static float data_to_change = 0;
