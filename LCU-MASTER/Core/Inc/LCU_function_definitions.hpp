
#include "CommonData/CommonData.hpp"
#include "LCU_MASTER.hpp"

void fix_buffer_reset_high(){
	Communication::ldu_index_to_change = Communication::ldu_number_to_change - 1;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset = true;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset_value = true;
}

void fix_buffer_reset_low(){
	Communication::ldu_index_to_change = Communication::ldu_number_to_change - 1;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset = true;
	LDU_Buffer::ldu_buffers[Communication::ldu_index_to_change].fixed_reset_value = false;
}
