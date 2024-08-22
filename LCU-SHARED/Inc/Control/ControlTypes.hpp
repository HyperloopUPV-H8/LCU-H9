#pragma once

#include "Tools/Tools.hpp"


/*  #############################################################
 *  ################### LCU_RUNNING_MODE  #######################
 *  #############################################################
 */

enum LCU_running_modes{
	//mostly deprecated, works the same as DOF5 but with the control of DOF1
	DOF1,

	//Uses different PWMs and sensors profiles and doesn t activate buffers, DO NOT USE OUT OF HIL
	DOF5_HIL,

	//All DOF5 implementations, minimum protections for current control and comms
	DOF5,

	//Same as DOF5, but with higher protections, including zeroing and all connections
	POD,
};
