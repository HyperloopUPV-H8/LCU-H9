#pragma once

#include "Tools/Tools.hpp"

static constexpr uint32_t LEVITATION_CONTROL_FREQ_HZ = 1000;
static constexpr double LEVITATION_CONTROL_PERIOD_SECONDS = (double) (1.0 / LEVITATION_CONTROL_FREQ_HZ);


#define KP_DOF1_AIRGAP_TO_CURRENT -11149.0 //-5500.0 //-4868.5
#define KI_DOF1_AIRGAP_TO_CURRENT -10518.0 //-1700.0 //-1030.1
#define KD_DOF1_AIRGAP_TO_CURRENT -1591.0 //-550.0 //-94.0
#define LEVITATION_CONTROL_MOVING_AVERAGE_SIZE 20

// 		y 		dy 		z 			dz 			rot_x 		drot_x	rot_y 		d_roty 	rot_z 	drot_z 	iy 		iz 		irot_x 		irot_y 		irot_z
static float initial_levitation_control_constants[10][15] = {
        {0.0, 	0.0, 	-5000.0, 	-200.0, 	 1400.0, 	 40.0, 	 2400.0, 	 80.0, 	0.0, 	0.0, 	0.0,	0.0, 	0.0, 	0.0, 	0.0},
        {0.0, 	0.0, 	-5000.0, 	-200.0, 	-1400.0, 	-40.0, 	 2400.0, 	 80.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0},
        {0.0, 	0.0, 	-5000.0, 	-200.0, 	 1400.0,   	 40.0, 	-2400.0, 	-80.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0},
        {0.0, 	0.0, 	-5000.0, 	-200.0, 	-1400.0, 	-40.0, 	-2400.0, 	-80.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0, 	0.0},
        {-4338.34213661919, -867.668427323838/2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1681.31234405778, -187.021839681972, -1204, 0.0, 0.0, 0.0, -3072.72935377977},
        {4338.34213661919, 867.668427323838/2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1681.31234405778, 187.021839681972, 1204, 0.0, 0.0, 0.0, 3072.72935377977},
        {-4338.34213661919, -867.668427323838/2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1204, 0.0, 0.0, 0.0, 0.0},
        {4338.34213661919, 867.668427323838/2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1204, 0.0, 0.0, 0.0, 0.0},
        {-4338.34213661919, -867.668427323838/2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1681.31234405778, 187.021839681972, -1204, 0.0, 0.0, 0.0, 3072.72935377977},
        {4338.34213661919, 867.668427323838/2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1681.31234405778, -187.021839681972, 1204, 0.0, 0.0, 0.0, -3072.72935377977}
};
