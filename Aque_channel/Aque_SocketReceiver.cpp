#include "Aque_SocketReceiver.h"

int SocketReceiver::init_socket()
{
    int fd = -1;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0)
    {
        lfatal("create new socket failed");
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_config.m_port);
    addr.sin_addr = inet_addr(m_config.m_ip.c_str());

    if(bind(fd,(struct sockaddr*)&addr,sizeof(struct sockaddr_in)) < 0)
    {
        lfatal("bind socket failed");
        return -1;
    }
    m_fd = fd;
    return 0;
}

int SocketReceiver::init_event()
{
    if(NULL == m_event_base)
    {
        lerror("event_base uninitialized");
        return -1;
    }
    m_event = event_new(m_event_base,m_fd,EV_PERSIST|EV_READ,do_collect_log,(void*)m_event_base);
    if(NULL == m_event)
    {
        lerror("create collect_log event failed");
        return -1;
    }

    if(event_add(m_event,NULL) < 0)
    {
        lerror("add event failed");
        return -1;
    }
    return 0;
}

int SocketReceiver::configReInit(std::string config)
{
    if(close(m_fd) < 0)
    {
        lfatal("close socket failed");
        return -1;
    }
    m_fd = -1;
    if(event_del(m_event) < 0)
    {
        lerror("delete event failed");
        return -1;
    }
    m_event = NULL;

    if(configInit(config) < 0)
    {
        lerror("init configure failed");
        return -1;
    }
    linfo("configInit success");
    return 0;
}

void* SocketReceiver::do_event(void* arg)
{
    event_base_dispatch(m_event_base);
}

int SocketReceiver::configInit(std::string config)
{
    if(config.empty())
    {
        lerror("SocketFile configure NULL");
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
    json_temp = cJSON_GetObjectItem(root,"ip");
    if(NULL == json_temp)
    {
        lerror("get ip address failed");
        return -1;
    }
    m_config.m_ip.assign(json_temp.valuestring);

    json_temp = cJSON_GetObjectItem(root,"port");
    if(NULL == json_temp)
    {
        lerror("get port failed");
        return -1;
    }
    m_config.m_port = json_temp.valueint;

    linfo("analysis configure success");

    if(init_socket() < 0)
    {
        lerror("init log socket failed");
        return -1;
    }
    linfo("init_socket success");

    if(init_event() < 0)
    {
        lerror("init event failed");
        return -1;
    }
    linfo("init_event success");
}

int SocketReceiver::receive()
{
    pthread_t ptid;

    if(pthread_create(&ptid,NULL,do_event,NULL) < 0)
    {
        lfatal("create new pthread failed");
        return -1;
    }
    return 0;
}

int SocketReceiver::stop()
{
    if(event_base_loopexit(m_event_base,NULL) < 0)
    {
        lerror("stop event_base_dispatch failed");
        return -1;
    }
    return 0;
}

int SocketReceiver::notifyChannel()
{
    if(raise(AQUE_SIG_SEND) < 0)
    {
        lfatal("send signal failed");
        return -1;
    }
    return 0;
}

int SocketReceiver::configChange()
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

run_state SocketReceiver::getRunState()
{
    return m_state;
}

int SocketReceiver::setRunState(run_state t_state)
{
    m_state = t_state;
    return 0;
}

SocketReceiver::SocketReceiver()
{
    m_event_base = event_base_new();
    if(NULL == m_event_base)
    {
        lerror("create new event base failed");
    }
}

