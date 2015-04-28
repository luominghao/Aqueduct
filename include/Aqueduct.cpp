#include "Aqueduct.h"
int Aqueduct::AqueductLog::initLogger(string apd_name,int lgr_level)
{
	if(lgr_level<0 || lgr_level>6)
	{
		LogLog::getLogLog()->error("logger level error");
		return -1;
	}
	SharedObjectPtr<Appender> append(new FileAppender(apd_name.c_str()));
	append->setName(apd_name.c_str());

	std::string pattern("%D [%-5p] [%-20l] -%m %n");
	std::auto_ptr<Layout> layout(new PatternLayout(pattern));

	append->setLayout(layout);
	
	Logger logger=Logger::getRoot();
	logger.addAppender(append);
	
	logger.setLogLevel(lgr_level*10000);
	
	linfo(logger,"initialize logger success");
	
	return 0;
}

Aqueduct::AqueductLogger Aqueduct::AqueductLog::getLogger()
{
	return Logger::getRoot();
}