#include "Airgaps/Airgaps.hpp"

uint8_t Airgaps::airgaps_index_array[AIRGAP_COUNT]{0};
uint16_t* Airgaps::airgaps_binary_data_pointer_array[AIRGAP_COUNT]{nullptr};
uint16_t Airgaps::airgaps_binary_data_array[AIRGAP_COUNT]{0};
IntegerMovingAverage<uint16_t, uint16_t, 0, 10> Airgaps::airgaps_average_binary_data_array[AIRGAP_COUNT]{};
float Airgaps::airgaps_data_array[AIRGAP_COUNT]{0.0};
