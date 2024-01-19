#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

#include "LCU_MASTER.hpp"

int main(void)
{
	static_assert(HSE_VALUE==25'000'000,"INVALID HSE value for BOARD");
	Communication::test_order_received = new DigitalOutput(PG4);
	DigitalOutput reset_5{PB14};
	uint8_t fault_10 = DigitalInput::inscribe(PE11);
	uint8_t ready_10 = DigitalInput::inscribe(PE10);


	LCU lcu_master;

	reset_5.turn_off();
	Communication::test_order_received->turn_on();
	uint8_t unused_variable = Time::set_timeout(3000,[&](){
		Communication::test_order_received->turn_off();
	});
	Communication comms;

	Time::register_low_precision_alarm(1000, [&](){Communication::duty_to_change = 50.0; Communication::pwm_to_change = 0;Communication::send_pwm_data();});


	while(1) {
		if(DigitalInput::read_pin_state(ready_10) == PinState::ON && DigitalInput::read_pin_state(fault_10) == PinState::ON){
			reset_5.turn_on();
		}else{
			reset_5.turn_off();
		}

		lcu_master.update();
	}
/*#ifdef MASTER
    SPI::instance3.mode = SPI_MODE_MASTER;
    DigitalOutput running_led(PG8);
    DigitalOutput error_led(PG7);
    DigitalOutput feedback_led(PG6);
    DigitalOutput compass_led(PG5);
#else
    SPI::instance3.mode = SPI_MODE_SLAVE;
#endif
    SPI::instance3.SS = &PD3; //<para la LCU, que tiene el chip select cambiado
    uint8_t spi_server = SPI::inscribe(SPI::spi3);
    SPIPacket hello(1000,4,4);
    STLIB::start();
#ifdef MASTER
    Time::register_low_precision_alarm(1000, [&](){
            SPI::master_transmit_packet(spi_server, hello);
    		compass_led.toggle();});
    running_led.turn_on();
#else
    hello.slave_data[3] = 16;
    SPI::slave_listen_packets(spi_server);
#endif
    while(1){
#ifdef MASTER
        hello.master_data[3] = 15; // < los dos primeros bits son aun la id (tengo que cambiar eso), por eso a pesar de ser tamaño 2 el payload puedes acceder hasta este bit (que es el ultimo)
        SPI::packet_update();
        if(hello.slave_data[3] == 16){ // < esto comienza a suceder en el segundo mensaje, cuando el slave ya envia 16.
        	hello.slave_data[3] = 0;
        	feedback_led.toggle();
        }
        if(ErrorHandlerModel::error_triggered){
        	error_led.turn_on();
        }
#else
        if(hello.master_data[3] == 15){ // < llega el primer mensaje y entonces el slave comienza a enviar 16 en el ultimo bit
            hello.master_data[3] = 0;
        }
#endif
        STLIB::update();
    }*/
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
