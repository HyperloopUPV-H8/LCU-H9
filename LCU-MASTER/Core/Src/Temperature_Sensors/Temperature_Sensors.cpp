#include "Temperature_Sensors/Temperature_Sensors.hpp"


float Temperature_Sensors::coil_temperature[LDU_COUNT]{0.0};
float Temperature_Sensors::lpu_temperature[LDU_COUNT]{0.0};

LinearSensor<float> Temperature_Sensors::coil_temperature_adc[LDU_COUNT]{};
NTC Temperature_Sensors::lpu_temperature_adc[LDU_COUNT]{};

uint32_t Temperature_Sensors::temperature_zeroing_count = 0;

FloatMovingAverage<TEMPERATURE_ZEROING_SAMPLE_AMOUNT> Temperature_Sensors::coil_temperature_zeroing_calculator[LDU_COUNT]{};
FloatMovingAverage<TEMPERATURE_ZEROING_SAMPLE_AMOUNT> Temperature_Sensors::lpu_temperature_zeroing_calculator[LDU_COUNT]{};

float Temperature_Sensors::coil_temperature_adc_zeroing[LDU_COUNT]{0.0};
float Temperature_Sensors::lpu_temperature_adc_zeroing[LDU_COUNT]{0.0};

bool Temperature_Sensors::zeroing_complete = false;
