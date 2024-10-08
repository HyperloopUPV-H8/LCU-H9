#pragma once

#include "Sensors/Sensors.hpp"

inline float DOF1_airgap_distance_binary_to_float(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_1DOF_AIRGAP_SLOPE + FLOAT_1DOF_AIRGAP_OFFSET;
}

inline float airgap_distance_binary_to_float(uint8_t id, uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_AIRGAP_SLOPE[id] + FLOAT_AIRGAP_OFFSET[id];
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

inline float coil_current_binary_to_real_HIL(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_SHUNT_SLOPE_HIL + FLOAT_SHUNT_OFFSET_HIL;
}

inline float battery_voltage_binary_to_real(uint16_t binary_value){
	return (binary_value / MAX_16BIT * ADC_MAX_VOLTAGE) * FLOAT_VBAT_SLOPE + FLOAT_VBAT_OFFSET;
}

inline uint16_t battery_voltage_binary_to_OBCCU(uint16_t binary_value){
	int result = ((int)binary_value)*((int)FLOAT_VBAT_SLOPE)/INT_ADC_BINARY_TO_VOLTAGE_BY_DIVISION + ((int)FLOAT_VBAT_OFFSET);
	if(result < 0){
		return 0;
	}
	return (uint16_t)result;
}
