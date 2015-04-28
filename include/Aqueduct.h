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

//AqueductLog macro define
#define 	ltrace		LOG4CPLUS_TRACE
#define 	ldebug 		LOG4CPLUS_DEBUG
#define 	linfo  		LOG4CPLUS_INFO
#define 	lwarn  		LOG4CPLUS_WARN
#define 	lerror 		LOG4CPLUS_ERROR
#define 	lfatal 		LOG4CPLUS_FATAL

#define     DEFAULT_LOG_LEVEL   0


namespace Aqueduct
{
	typedef Logger AqueductLogger;
	class AqueductLog
	{
	public:
		static int initLogger(string apd_name,int lgr_level);
		static AqueductLogger getLogger();
	};
}
