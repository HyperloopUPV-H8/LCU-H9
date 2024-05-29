#pragma once

#include "Tools/Tools.hpp"


enum LCU_states{
	DEFINING = 0b00000001,
	INITIAL = 0b00100000,
	OPERATIONAL = 0b01010000,
	FAULT = 0b11111111,
};

static struct lcu_status_flags{
	bool enable_current_control = false;
	bool enable_levitation_control = false;
	bool enable_lateral_levitation_control = false;
	bool enable_nominal_control = false;
	bool fault_flag = false;
}status_flags;
