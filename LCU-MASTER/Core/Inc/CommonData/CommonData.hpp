#pragma once

#include "ST-LIB.hpp"

static const uint8_t LDU_COUNT = 10;


static IPV4 MASTER_IP("192.168.1.4");
static IPV4 BACKEND("192.168.0.9");
static const uint32_t TCP_SERVER_PORT = 50500;
static const uint32_t TCP_CLIENT_PORT = 50401;
static const uint32_t UDP_PORT = 50400;

static const uint16_t TEST_PWM_1_PACKET_ID = 1001;
static const uint16_t TEST_PWM_PACKET_AMOUNT = LDU_COUNT*2;
static const uint8_t TEST_PWM_PACKET_DUTY_BYTE = 2;
static const uint8_t TEST_PWM_PACKET_FREQ_BYTE = 6;
