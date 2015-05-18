#include "Aque_receiver.h"

class SocketReceiver:public Aque_receiver
{
private:
    int                     m_fd;
    struct event_base*      m_event_base;
    struct event*           m_event;
    struct sock_recv_cfg    m_config;

    int init_socket();
    int init_event();
    int configReInit(std::string config);
    void *do_event(void* arg);

public:
    virtual int configInit(std::string config);
	virtual int receive();
	virtual int stop();
	virtual int notifyChannel();
	virtual int configChange();
	virtual run_state getRunState();
	virtual int setRunState(run_state t_state);
	SocketReceiver();

};

struct sock_recv_cfg
{
    std::string             m_ip;
    int                     m_port;
};
