#pragma once

#include "Sensors/Sensors.hpp"

inline float DOF1_airgap_distance_binary_to_float(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_1DOF_AIRGAP_SLOPE + FLOAT_1DOF_AIRGAP_OFFSET;
}

inline float EMS_airgap_distance_binary_to_float(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_EMS_AIRGAP_SLOPE + FLOAT_EMS_AIRGAP_OFFSET;
}

inline float HEMS_airgap_distance_binary_to_float(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_HEMS_AIRGAP_SLOPE + FLOAT_HEMS_AIRGAP_OFFSET;
}

inline float coil_current_binary_to_real(uint8_t id, uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_SHUNT_SLOPE[id] + FLOAT_SHUNT_OFFSET[id];
}

inline float battery_voltage_binary_to_real(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_VBAT_SLOPE + FLOAT_VBAT_OFFSET;
}
