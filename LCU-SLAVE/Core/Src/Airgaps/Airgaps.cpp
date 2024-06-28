#include "Airgaps/Airgaps.hpp"

uint8_t Airgaps::airgaps_index_array[AIRGAP_COUNT]{0};
uint16_t* Airgaps::airgaps_binary_data_pointer_array[AIRGAP_COUNT]{nullptr};
uint16_t Airgaps::airgaps_binary_data_array[AIRGAP_COUNT]{0};
IntegerMovingAverage<uint16_t, uint16_t, 0, 10> Airgaps::airgaps_average_binary_data_array[AIRGAP_COUNT]{};
float Airgaps::airgaps_data_array[AIRGAP_COUNT]{0.0};

IntegerMovingAverage<uint32_t, uint32_t, 0, CURRENT_ZEROING_SAMPLE_AMOUNT> Airgaps::horizontal_airgap_sumation_zeroing_5_6;
IntegerMovingAverage<uint32_t, uint32_t, 0, CURRENT_ZEROING_SAMPLE_AMOUNT> Airgaps::horizontal_airgap_sumation_zeroing_7_8;
uint32_t Airgaps::zeroing_sample_count = 0;
int32_t Airgaps::expected_horizontal_airgap_sumation_5_6 = 0;
int32_t Airgaps::expected_horizontal_airgap_sumation_7_8 = 0;
bool Airgaps::horizontal_airgap_zeroing_complete = false;
int32_t Airgaps::noise = 0;
