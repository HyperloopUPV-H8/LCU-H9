#include "../../../nCore/Inc/Communication/Communication.hpp"

#include "ST-LIB.hpp"

uint8_t Communication::spi_id = 0;
SPIPacket* Communication::test_pwm_packets[TEST_PWM_PACKET_AMOUNT]{nullptr};
