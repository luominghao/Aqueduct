#include <string>
#include "Aqueduct.h"

using namespace std;

class Aque_receiver
{
protected:
	run_state m_state;
public:
	virtual int configInit();
	virtual int receive();
	virtual int stop();
	virtual int notifyChannel();
	virtual int configChange();
	virtual run_state getRunState();
	virtual int setRunState();
	Aque_receiver();
};