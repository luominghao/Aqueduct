#include "Aqueduct.h"
#include <queue>

typedef struct run_state_t
{
	int    		state;
	int 		speed;
	int 		log_num;
	long 		total_byte;
	time_t 		start_time;
}run_state;

class Aque_channel
{
private:
	std::queue<std::string> m_msgQueue;
	run_state m_senderState;
	run_state m_receiverState;
	int m_socket;
	
};