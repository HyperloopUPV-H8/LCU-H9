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

static constexpr uint32_t SPI_ORDER_COUNT = 1;

static const uint16_t TEST_PWM_PACKET_ID = 1001;
static constexpr uint16_t TEST_PWM_ORDER_INDEX = 0;
static const uint16_t TEST_PWM_PACKET_AMOUNT = LDU_COUNT*2;
