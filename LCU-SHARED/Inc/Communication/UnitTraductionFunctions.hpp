#pragma once

#include "Sensors/Sensors.hpp"

inline float airgap_distance_binary_to_real(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * DOUBLE_AIRGAP_SLOPE + DOUBLE_AIRGAP_OFFSET;
}

inline float coil_current_binary_to_real(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * DOUBLE_AIRGAP_SLOPE + DOUBLE_AIRGAP_OFFSET;
}

inline float battery_voltage_binary_to_real(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * DOUBLE_AIRGAP_SLOPE + DOUBLE_AIRGAP_OFFSET;
}
