#pragma once

#include "Layout/Layout.hpp"
#include "Sensors/Sensors.hpp"
#include "Control/Control.hpp"
#include "Tools/Tools.hpp"
#include "Communication/Communication.hpp"


constexpr LCU_running_modes RUNNING_MODE = DOF5_HIL_FLOAT;

//TODO: DEFINE THIS WHILE WORKING WITH LPUs!!!
//#define BOARD_PROTECTIONS

#if (RUNNING_MODE == DOF5_FLOAT || RUNNING_MODE == DOF5_FIXED || RUNNING_MODE == DOF5_HIL_FLOAT)
#define USING_DOF5_CONFIG
#else
#define USING_DOF1_CONFIG
#endif

#if (RUNNING_MODE == DOF5_FIXED)
#define ARITHMETIC_MODE uint32_t
#define USING_FIXED_ARITHMETIC
#else
#define ARITHMETIC_MODE float
#define USING_FLOATING_ARITHMETIC
#endif
