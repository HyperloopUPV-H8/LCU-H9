#include "ST-LIB.hpp"
#include "Communication/Communication.hpp"

uint8_t Communication::spi_id = 0;
ServerSocket* Communication::gui_connection = nullptr;
DatagramSocket* Communication::udp_connection = nullptr;

DigitalOutput* Communication::test_order_received = nullptr;
Order* Communication::EthernetOrders[ETH_ORDER_COUNT]{nullptr};

uint16_t Communication::ldu_to_change = 0;
float Communication::duty_to_change = 0;
bool Communication::new_slave_data = false;

