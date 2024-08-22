#pragma once

#include "Tools/Tools.hpp"


enum LCU_states{
	DEFINING = 0,
	INITIAL = 1,
	OPERATIONAL = 2,
	FAULT = 3,
};

enum levitation_states{
	IDLE = 0,
	VERTICAL_LEVITATION,
	COMPLETE_LEVITATION,
	BOOSTING,
	DISCHARGING,
};

static struct lcu_status_flags{
	bool enable_current_control = false;
	bool enable_levitation_control = false;
	bool enable_lateral_levitation_control = false;
	bool enable_nominal_control = false;
	bool fault_flag = false;
}status_flags;
