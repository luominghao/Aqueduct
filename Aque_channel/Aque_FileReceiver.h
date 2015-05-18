#include "Aque_receiver.h"

#include "cJSON.h"

#include <pthread.h>

class FileReceiver:public Aque_receiver
{
private:
    int recv_fd;
    struct event_base *e_base;
    struct event *e_timer;
    struct FileReceiver_configure m_config;

    int init_sock();
    int init_event();
    int configReInit(std::string config);
    void* do_event(void* arg);

public:
    virtual int configInit(std::string config);
	virtual int receive();
	virtual int stop();
	virtual int notifyChannel();
	virtual int configChange();
	virtual run_state getRunState();
	virtual int setRunState(run_state t_state);
	FileReceiver();
};

struct FileReceiver_configure
{
    std::string         log_file_path;
    int                 inval_time;
};
