#include <string>
#include "Aqueduct.h"

using namespace std;

class Aque_sender
{
protected:
	run_state m_state;
public:
	virtual int configInit(string cfg);
	virtual int send();
	virtual int stop();
	virtual void configChange();
	virtual int getRunState();
	virtual int setRunState();
	Aque_sender();
};