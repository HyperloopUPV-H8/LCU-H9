#pragma once

#include "Layout/Layout.hpp"
#include "Sensors/Sensors.hpp"
#include "Control/Control.hpp"
#include "Tools/Tools.hpp"
#include "Communication/Communication.hpp"


#define ARITHMETIC_MODE float
constexpr LCU_running_modes RUNNING_MODE = DOF5;


uint8_t initial_exchange_value(){
	return LCU_states::INITIAL || RUNNING_MODE;
}
