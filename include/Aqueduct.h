#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <unistd.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/helpers/loglog.h>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

#pragma once

//AqueductLog macro define
#define 	ltrace(s)	    LOG4CPLUS_TRACE(AqueductLog::logger,s)
#define 	ldebug(s) 		LOG4CPLUS_DEBUG(AqueductLog::logger,s)
#define 	linfo(s)  		LOG4CPLUS_INFO(AqueductLog::logger,s)
#define 	lwarn(s)  		LOG4CPLUS_WARN(AqueductLog::logger,s)
#define 	lerror(s) 		LOG4CPLUS_ERROR(AqueductLog::logger,s)
#define 	lfatal(s) 		LOG4CPLUS_FATAL(AqueductLog::logger,s <<":"<<strerror(errno))
//Default log level define
#define     DEFAULT_LOG_LEVEL   0

//run state macro define


//some common macro define start
#define AQUE_SOCK_PATH          "/tmp/aqueduct/"
#define AQUE_MONITOR            "monitor"
#define AQUE_CONNECT_MAX        16
#define AQUE_COLLECT_INTERVAL   5

//some common macro define end

enum RUN_STATE
{
    RUN_STATE_MIN,
    RUN_STATE_START,
    RUN_STATE_STARTTING,
    RUN_STATE_RUNNING,
    RUN_STATE_STOPPING,
    RUN_STATE_STOP,
    RUN_STATE_MAX
};

//define command type
enum CMD_TYPE
{
    CMD_TYPE_MIN,
    CMD_TYPE_CFG_REQUEST,		//request configure data
    CMD_TYPE_CFG_REPLY,			//request configure data reply
    CMD_TYPE_STATE_REQUEST,		//run state information request
    CMD_TYPE_STATE_REPLY,		//run state information reply
    CMD_TYPE_CFG_NOTIFY,		//notify configure changed
    CMD_TYPE_MAX
};

//Aqueduct log handle class
class AqueductLog
{
    public:
        static Logger logger;
        static int initLogger(string apd_name, int lgr_level);
};

