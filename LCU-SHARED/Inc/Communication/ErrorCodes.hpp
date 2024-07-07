#pragma once

#include "Tools/Tools.hpp"

enum ERROR_CODES: uint16_t{
	ERROR_HANDLER_TRIGGERED = 1,
	MASTER_NOT_IN_SAME_MODE = 2,
	MASTER_SENT_TO_FAULT = 3,
	LDU_ZEROING_FAILED = 11, //11 to 20
	LDU_CURRENT_LIMIT = 21, //21 to 30
	AIRGAP_OUT_OF_RANGE = 31, //31 to 38
};


static unordered_map<uint16_t,string> error_codes_messages{
	{0,"Unknown slave error"},
	{1,"Error handler triggered on slave"},
	{2,"Master and slave are not in the same mode"},
	{3,"Master sent to fault the slave"},
	{11,"Zeroing on LDU 1 failed, the cable may not be properly connected"},
	{12,"Zeroing on LDU 2 failed, the cable may not be properly connected"},
	{13,"Zeroing on LDU 3 failed, the cable may not be properly connected"},
	{14,"Zeroing on LDU 4 failed, the cable may not be properly connected"},
	{15,"Zeroing on LDU 5 failed, the cable may not be properly connected"},
	{16,"Zeroing on LDU 6 failed, the cable may not be properly connected"},
	{17,"Zeroing on LDU 7 failed, the cable may not be properly connected"},
	{18,"Zeroing on LDU 8 failed, the cable may not be properly connected"},
	{19,"Zeroing on LDU 9 failed, the cable may not be properly connected"},
	{20,"Zeroing on LDU 10 failed, the cable may not be properly connected"},
	{21,"LDU 1 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{22,"LDU 2 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{23,"LDU 3 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{24,"LDU 4 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{25,"LDU 5 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{26,"LDU 6 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{27,"LDU 7 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{28,"LDU 8 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{29,"LDU 9 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{30,"LDU 10 surpassed maximum allowed current, or the cable to the LDU may have been disconnected"},
	{31,"Airgap 1 out of range, either noise is too high or the cable is disconnected"},
	{32,"Airgap 2 out of range, either noise is too high or the cable is disconnected"},
	{33,"Airgap 3 out of range, either noise is too high or the cable is disconnected"},
	{34,"Airgap 4 out of range, either noise is too high or the cable is disconnected"},
	{35,"Airgap 5 out of range, either noise is too high or the cable is disconnected"},
	{36,"Airgap 6 out of range, either noise is too high or the cable is disconnected"},
	{37,"Airgap 7 out of range, either noise is too high or the cable is disconnected"},
	{38,"Airgap 8 out of range, either noise is too high or the cable is disconnected"},
};
