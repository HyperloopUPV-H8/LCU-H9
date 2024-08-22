#include "ST-LIB.hpp"
#include "Communication/Communication.hpp"

uint8_t Communication::spi_id = 0;

ServerSocket *Communication::gui_connection = nullptr; //TODO: remove this for good
ServerSocket *Communication::vcu_connection = nullptr;
DatagramSocket *Communication::upd_gui = nullptr;
DatagramSocket *Communication::udp_vcu = nullptr;

DigitalOutput* Communication::test_order_received = nullptr;
Order* Communication::EthernetOrders[ETH_ORDER_COUNT]{nullptr};
Packet* Communication::EthernetPackets[ETH_PACKET_COUNT]{nullptr};

uint32_t Communication::last_current_control_count_for_frequency = 0;
uint32_t Communication::last_levitation_control_count_for_frequency = 0;
uint32_t Communication::current_control_frequency = 0;
uint32_t Communication::levitation_control_frequency = 0;

Communication::communication_flags Communication::flags{};

uint16_t Communication::ldu_number_to_change = 0;
uint16_t Communication::ldu_index_to_change = 0;
float Communication::duty_to_change = 0;
float Communication::data_from_backend = 0;
float Communication::data_to_change = 0;
bool Communication::new_slave_data = false;

