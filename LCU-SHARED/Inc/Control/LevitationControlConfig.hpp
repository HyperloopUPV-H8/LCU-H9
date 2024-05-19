#pragma once

#include "Tools/Tools.hpp"

static constexpr uint32_t LEVITATION_CONTROL_FREQ_HZ = 1000;
static constexpr double LEVITATION_CONTROL_PERIOD_SECONDS = (double) (1.0 / LEVITATION_CONTROL_FREQ_HZ);


#define KP_DOF1_AIRGAP_TO_CURRENT -11149.0 //-5500.0 //-4868.5
#define KI_DOF1_AIRGAP_TO_CURRENT -10518.0 //-1700.0 //-1030.1
#define KD_DOF1_AIRGAP_TO_CURRENT -1591.0 //-550.0 //-94.0
#define LEVITATION_CONTROL_MOVING_AVERAGE_SIZE 20


/*static float initial_levitation_control_constants[10][15] = {
        {0.0, 0.0, -6180.32698290269, -500.0, 4609.17728844817, 500.0, 3431.55213140212, 0.5*130.0, 0.0, 0.0, 0.0, -8000.0, 5529.48259026784, 5374.20729399096, 0.0},
        {0.0, 0.0, -6180.32698290269, -500.0, -4609.17728844817, -500.0, 3431.55213140212, 0.5*130.0, 0.0, 0.0, 0.0, -8000.0, -5529.48259026784, 5374.20729399096, 0.0},
        {0.0, 0.0, -6180.32698290269, -500.0, 4609.17728844817, 500.0, -3431.55213140212, 0.5*-130.0, 0.0, 0.0, 0.0, -8000.0, 5529.48259026784, -5374.20729399096, 0.0},
        {0.0, 0.0, -6180.32698290269, -500.0, -4609.17728844817, -500.0, -3431.55213140212, 0.5*-130.0, 0.0, 0.0, 0.0, -8000.0, -5529.48259026784, -5374.20729399096, 0.0},
        {-4338.34213661919, -867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1681.31234405778, -187.021839681972, -1204, 0.0, 0.0, 0.0, -3072.72935377977},
        {4338.34213661919, 867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1681.31234405778, 187.021839681972, 1204, 0.0, 0.0, 0.0, 3072.72935377977},
        {-4338.34213661919, -867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1204, 0.0, 0.0, 0.0, 0.0},
        {4338.34213661919, 867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1204, 0.0, 0.0, 0.0, 0.0},
        {-4338.34213661919, -867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1681.31234405778, 187.021839681972, -1204, 0.0, 0.0, 0.0, 3072.72935377977},
        {4338.34213661919, 867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1681.31234405778, -187.021839681972, 1204, 0.0, 0.0, 0.0, -3072.72935377977}
};*/

static float initial_levitation_control_constants[10][15] = {
        {0.0, 0.0, -6180.32698290269, -500.0, 4609.17728844817, 500.0, 3431.55213140212, 0.5*130.0, 0.0, 0.0, 0.0, -8000.0, 5529.48259026784, 5374.20729399096, 0.0},
        {0.0, 0.0, -6180.32698290269, -500.0, -4609.17728844817, -500.0, 3431.55213140212, 0.5*130.0, 0.0, 0.0, 0.0, -8000.0, -5529.48259026784, 5374.20729399096, 0.0},
        {0.0, 0.0, -6180.32698290269, -500.0, 4609.17728844817, 500.0, -3431.55213140212, 0.5*-130.0, 0.0, 0.0, 0.0, -8000.0, 5529.48259026784, -5374.20729399096, 0.0},
        {0.0, 0.0, -6180.32698290269, -500.0, -4609.17728844817, -500.0, -3431.55213140212, 0.5*-130.0, 0.0, 0.0, 0.0, -8000.0, -5529.48259026784, -5374.20729399096, 0.0},
        {-4338.34213661919, -867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, -1204, 0.0, 0.0, 0.0, 0},
        {4338.34213661919, 867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 1204, 0.0, 0.0, 0.0, 0},
        {-4338.34213661919, -867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1204, 0.0, 0.0, 0.0, 0.0},
        {4338.34213661919, 867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1204, 0.0, 0.0, 0.0, 0.0},
        {-4338.34213661919, -867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, -1204, 0.0, 0.0, 0.0, 0},
        {4338.34213661919, 867.668427323838/4, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 1204, 0.0, 0.0, 0.0, 0}
};
