#include "Aque_FileReceiver.h"

FileReceiver::FileReceiver()
{
    recv_fd = -1;
    e_timer = NULL;

    e_base = event_base_new();

    if(NULL == e_base)
    {
        lerror("create new event_base failed");
    }
}

//FileReceiver configure file analysis
int FileReceiver::configInit(std::string config)
{
    if(config.empty())
    {
        lerror("FileReceiver configure NULL");
        return -1;
    }
    cJSON *root = NULL;
    cJSON *json_temp = NULL;
    root = cJSON_Parse(config.c_str());

    if(NULL == root)
    {
        lerror("analysis configure failed");
        return -1;
    }

    json_temp = cJSON_GetObjectItem(root,"path");
    if(NULL == json_temp)
    {
        lerror("get log file path failed");
        return -1;
    }
    m_config.log_file_path.assign(json_temp.valuestring);

    json_temp = cJSON_GetObjectItem(root,"time");
    if(NULL == json_temp)
    {
        lerror("get interval time failed");
        return -1;
    }
    m_config.inval_time = json_temp.valueint;

    if(init_sock() < 0)
    {
        lerror("init read socket failed");
        return -1;
    }
    linfo("init_sock success");

    if(init_event() < 0)
    {
        lerror("init event failed");
        return -1;
    }
    linfo("init_event success");

    linfo("init FileReceiver success");
}
int FileReceiver::init_sock()
{
    recv_fd = open(m_config.log_file_path,O_RDONLY);

    if(recv_fd < 0)
    {
        lfatal("open log file failed");
        return -1;
    }
    return 0;
}

int FileReceiver::init_event()
{
    if(NULL == e_base)
    {
        lerror("event_base uninitialized");
        return -1;
    }

    e_timer = event_new(e_base,-1,EV_PERSIST,do_collect_log,(void*)e_base);

    if(NULL == e_timer)
    {
        lerror("create collect_log event failed");
        return -1;
    }
    if(event_add(e_timer,m_config.inval_time) < 0)
    {
        lerror("add e_timer failed");
        return -1;
    }
    return 0;
}

int FileReceiver::receive()
{
    pthread_t ptid;

    if(pthread_create(&ptid,NULL,do_event,NULL) < 0)
    {
        lfatal("create new pthread failed");
        return -1;
    }
    return 0;
}
void FileReceiver::do_event(void* arg)
{
    event_base_dispatch(e_base);
}

int FileReceiver::stop()
{
    if(event_base_loopexit(e_base,NULL) < 0)
    {
        lerror("stop event_base_dispatch failed");
        return -1;
    }
    return 0;
}
int FileReceiver::configReInit(std::string config)
{
    if(close(recv_fd) < 0)
    {
        lfatal("close file failed");
        return -1;
    }
    recv_fd = -1;

    if(event_del(e_timer) < 0)
    {
        lerror("delete event timer failed");
        return -1;
    }
    e_timer = NULL;

    if(configInit(config) < 0)
    {
        lerror("init configure failed");
        return -1;
    }
    linfo("configInit success");
    return 0;
}

int FileReceiver::notifyChannel()
{
    if(raise(AQUE_SIG_SEND) < 0)
    {
        lfatal("send signal failed");
        return -1;
    }
    return 0;
}

int FileReceiver::configChange()
{
    if(stop() < 0)
    {
        lerror("stop log receive failed");
        return -1;
    }
    linfo("stop log receive success");

    if(configReInit() < 0)
    {
        lerror("reinit configure failed");
        return -1;
    }
    linfo("configReInit success");

    if(receive() < 0)
    {
        lerror("receive log failed");
        return -1;
    }
    linfo("configure change success");

    return 0;
}

run_state FileReceiver::getRunState()
{
    return m_state;
}

int FileReceiver::setRunState(run_state t_state)
{
    m_state = t_state;
    return 0;
}
