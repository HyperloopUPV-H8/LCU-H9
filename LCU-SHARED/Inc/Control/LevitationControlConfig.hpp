#pragma once

#include "Tools/Tools.hpp"

static constexpr uint32_t LEVITATION_CONTROL_FREQ_HZ = 1000;
static constexpr double LEVITATION_CONTROL_PERIOD_SECONDS = (double) (1.0 / LEVITATION_CONTROL_FREQ_HZ);

static constexpr uint32_t LEVITATION_STABILITY_CHECK_FREQ_HZ = 20;
static constexpr uint32_t LEVITATION_STABILITY_CHECK_CALCULATION_SPAN = LEVITATION_STABILITY_CHECK_FREQ_HZ;
static constexpr double LEVITATION_STABILITY_CHECK_PERIOD_SECONDS= (double) (1.0 / LEVITATION_STABILITY_CHECK_FREQ_HZ);
static constexpr float MAXIMUM_PEAK_LEVITATION_DEVIATION[5]{0.0003, 0.0003, 0.0005, 0.0005, 0.0005};
static constexpr float MAXIMUM_AVERAGE_LEVITATION_DEVIATION[5]{0.0003, 0.0003, 0.0005, 0.0005, 0.0005};


#define KP_DOF1_AIRGAP_TO_CURRENT -11149.0 //-5500.0 //-4868.5
#define KI_DOF1_AIRGAP_TO_CURRENT -10518.0 //-1700.0 //-1030.1
#define KD_DOF1_AIRGAP_TO_CURRENT -1591.0 //-550.0 //-94.0
#define LEVITATION_CONTROL_DOF1_MOVING_AVERAGE_SIZE 20
#define LEVITATION_CONTROL_DOF5_DERIVATIVE_MOVING_AVERAGE_SIZE 20

// 		y 		dy 		z 			dz 			rot_x 		drot_x	rot_y 		d_roty 	rot_z 	drot_z 	iy 		iz 		irot_x 		irot_y 		irot_z


static float initial_levitation_control_constants[10][15] = {
		{0.0, 0.0, -6180.0, -200.0,  1000.0,  60.0,  3600.0,  110.0, 0.0, 0.0, 0.0, -800.0,  300.0,  300.0, 0.0},
		{0.0, 0.0, -6180.0, -200.0, -1000.0, -60.0,  3600.0,  110.0, 0.0, 0.0, 0.0, -800.0, -300.0,  300.0, 0.0},
		{0.0, 0.0, -6180.0, -200.0,  1000.0,  60.0, -3600.0, -110.0, 0.0, 0.0, 0.0, -800.0,  300.0, -300.0, 0.0},
		{0.0, 0.0, -6180.0, -200.0, -1000.0, -60.0, -3600.0, -110.0, 0.0, 0.0, 0.0, -800.0, -300.0, -300.0, 0.0},
		{-1000.0, -210.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1681.31234405778, -187.021839681972, -500.0, 0.0, 0.0, 0.0, -3072.7/10},
        {1000.0, 210.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1681.31234405778, 187.021839681972, 500.0, 0.0, 0.0, 0.0, 3072.7/10},
        {-1000.0, -210.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -500.0, 0.0, 0.0, 0.0, 0.0},
        {1000.0, 210.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 500.0, 0.0, 0.0, 0.0, 0.0},
        {-1000.0, -210.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1681.31234405778, 187.021839681972, -500.0, 0.0, 0.0, 0.0, 3072.7/10},
        {1000.0, 210.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1681.31234405778, -187.021839681972, 500.0, 0.0, 0.0, 0.0, -3072.7/10}
};

