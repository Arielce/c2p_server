#ifndef LOBBYSERVER_HEADER_H
#define LOBBYSERVER_HEADER_H

#include <string>
#include <map>
#include <iostream>
#include <boost/lexical_cast.hpp>

//#include <log4cplus/helpers/loglog.h>
//#include <log4cplus/helpers/stringhelper.h>
//#include <log4cplus/ndc.h>
//#include <log4cplus/consoleappender.h>
//#include <log4cplus/layout.h>
//#include <log4cplus/helpers/loglog.h>
//#include <log4cplus/helpers/stringhelper.h>
//#include <log4cplus/loggingmacros.h>


#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif

#include "../network/INetCluster.h"

using namespace std;

#define TRACELOG(logEvent)	LOG4CPLUS_TRACE(g_gsLog, logEvent)
#define CTRACELOG(logEvent)	LOG4CPLUS_TRACE(g_clientLog, logEvent)
#define DEBUGLOG(logEvent)	LOG4CPLUS_DEBUG(g_gsLog, logEvent)
#define INFOLOG(logEvent)	LOG4CPLUS_INFO(g_gsLog, logEvent)
#define WARNLOG(logEvent)	LOG4CPLUS_WARN(g_gsLog, logEvent)
#define ERRORLOG(logEvent)	LOG4CPLUS_ERROR(g_gsLog, logEvent)
#define FATALLOG(logEvent)	LOG4CPLUS_FATAL(g_gsLog, logEvent)

#endif