#pragma once

#include "Communication/Communication.hpp"
#include "CommonData/CommonData.hpp"

class LCU{
public:
	Communication communication;

	LCU();
	void start();
	void update();

};
