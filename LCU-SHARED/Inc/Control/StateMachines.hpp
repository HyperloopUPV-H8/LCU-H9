#pragma once

#include "Tools/Tools.hpp"


enum LCU_states{
	INITIAL = 0,
	OPERATIONAL,
	FAULT,
};

static struct lcu_status_flags{
	bool enable_current_control = false;
	bool enable_levitation_control = false;
	bool enable_nominal_control = false;
	bool fault_flag = false;
}status_flags;
