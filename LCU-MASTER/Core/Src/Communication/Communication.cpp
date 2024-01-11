#include "ST-LIB.hpp"
#include "Communication/Communication.hpp"

uint8_t Communication::spi_id = 0;
SPIPacket* Communication::test_pwm_packets[TEST_PWM_PACKET_AMOUNT]{nullptr};
ServerSocket* Communication::gui_connection = nullptr;
DatagramSocket* Communication::udp_connection = nullptr;
uint8_t Communication::pwm_to_change = 0;
float Communication::duty_to_change = 0;

