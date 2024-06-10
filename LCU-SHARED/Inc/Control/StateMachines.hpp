#pragma once

#include "Tools/Tools.hpp"


enum LCU_states{
	DEFINING = 0b00000000,
	INITIAL = 0b00100000,
	OPERATIONAL = 0b01010000,
	FAULT = 0b11111111,
};

enum levitation_states{
	IDLE,
	TAKING_OFF,
	DOF3_STABLE,
	DOF5_STABLE,
	BOOSTER,
	LANDING,
	TESTING,
};
