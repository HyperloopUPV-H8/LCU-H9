#include "CommonData/CommonData.hpp"

class LEDs{
	uint8_t OperationalLedID = 0;
	uint8_t FaultLedID = 0;
	uint8_t CanLedID = 0;
	uint8_t FlashLedID = 0;
	uint8_t SleepLedID = 0;
public:

	LEDs(){
		OperationalLedID = DigitalOutputService::inscribe(OPERATIONAL_LED_PIN);
		FaultLedID = DigitalOutputService::inscribe(FAULT_LED_PIN);
		CanLedID = DigitalOutputService::inscribe(CAN_LED_PIN);
		FlashLedID = DigitalOutputService::inscribe(FLASH_LED_PIN);
		SleepLedID = DigitalOutputService::inscribe(SLEEP_LED_PIN);
	}

	void Set_Operational_Led(){
		DigitalOutputService::turn_off(FaultLedID);
		DigitalOutputService::turn_on(OperationalLedID);
	}

	void Set_Fault_Led(){
		DigitalOutputService::turn_on(FaultLedID);
		DigitalOutputService::turn_off(OperationalLedID);
	}
};
