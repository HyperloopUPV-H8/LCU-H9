#pragma once

#include "Tools/Tools.hpp"

static constexpr float TEMPERATURE_SLOPE = -795.45;
static constexpr float TEMPERATURE_OFFSET = 1273.9;

static constexpr uint32_t TEMPERATURE_UPDATE_DATA_HZ = 1000;
static constexpr double TEMPERATURE_UPDATE_PERIOD_SECONDS = (double) (1.0 / TEMPERATURE_UPDATE_DATA_HZ);


static constexpr uint32_t TEMPERATURE_ZEROING_SAMPLING_FREQUENCY_HZ = (400);
static constexpr double TEMPERATURE_ZEROING_SAMPLING_PERIOD_SECONDS = (double) (1.0 / TEMPERATURE_ZEROING_SAMPLING_FREQUENCY_HZ);
static constexpr uint32_t TEMPERATURE_ZEROING_SAMPLE_AMOUNT = 1000;

static constexpr float LPU_TEMPERATURE_ZEROING_MAXIMUM_LIMIT = 100.0;
static constexpr float COIL_TEMPERATURE_ZEROING_MAXIMUM_LIMIT = 100.0;
static constexpr float LPU_TEMPERATURE_MAXIMUM_LIMIT = 100.0;
static constexpr float COIL_TEMPERATURE_MAXIMUM_LIMIT = 100.0;
