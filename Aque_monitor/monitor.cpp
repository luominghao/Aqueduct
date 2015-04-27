#include <iostream>
#include <unistd.h>
#include "Aqueduct.h"

//internal function declare start
static int  resolveOpt(int argc,char *argv[]);

//internal function declare end
using namespace Aqueduct;

int main(int argc,char *argv[])
{
	if(resolveOpt(argc,argv) < 0)
	{
		LogLog::getLogLog()->error("resolve option error");;
		return -1;
	}
	
	AqueductLogger logger=AqueductLog::getLogger();
	lfatal(logger,"this is a fatal test");
	lerror(logger,"this is a error test");
	
	linfo(logger,"resolve option success");
	return 0;
}

static int resolveOpt(int argc,char *argv[])
{
	string optString("l:");
	int optCh = -1;
	
	string app_name(argv[0]);
	int lgr_level=DEFAULT_LOG_LEVEL;
	
	while((optCh=getopt(argc,argv,optString.c_str())) != -1)
	{
		switch(optCh)
		{
			case 'l':
			{
				lgr_level=atoi(optarg);
			}
			break;
			default:
			{
				LogLog::getLogLog()->error("resolve argv error");
				return -1;
			}
		}
	}
	
	if(AqueductLog::initLogger(app_name+"_log",lgr_level) < 0)
	{
		LogLog::getLogLog()->error("initLogger error");
		return -1;
	}
	return 0;
}