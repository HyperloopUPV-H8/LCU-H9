#pragma once

#include "ST-LIB.hpp"
#include "CommonCData.h"

static const uint8_t LDU_COUNT = 10;

static ip_addr_t master_ip_addr = IPADDR4_INIT_BYTES(MASTER_IP_B0,MASTER_IP_B1,MASTER_IP_B2,MASTER_IP_B3);
static IPV4 MASTER_IP(master_ip_addr);
static IPV4 BACKEND("192.168.0.9");
static const uint32_t TCP_SERVER_PORT = 50500;
static const uint32_t TCP_CLIENT_PORT = 50401;
static const uint32_t UDP_PORT = 50400;

static const uint16_t TEST_PWM_TCP_PACKET_ID = 350;

static const uint16_t TEST_PWM_1_PACKET_ID = 1001;
static const uint16_t TEST_PWM_PACKET_AMOUNT = LDU_COUNT*2;
static const uint8_t TEST_PWM_PACKET_DUTY_BYTE = 0;
static const uint8_t TEST_PWM_PACKET_MASTER_SIZE = 4;
static const uint8_t TEST_PWM_PACKET_SLAVE_SIZE = 4;
