#include "Airgaps/Airgaps.hpp"

uint8_t Airgaps::airgaps_index_array[AIRGAP_COUNT]{0};
double Airgaps::airgaps_raw_data_array[AIRGAP_COUNT]{0};
MovingAverage<AIRGAP_MOVING_AVERAGE_COUNT> Airgaps::airgaps_data_array[AIRGAP_COUNT]{};
