#include"demo.h"
#include"../CommonLib/LogLib/log4z.h"
using namespace zsummer::log4z;


int main()
{
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);

	LOGD("start");
	LOGD("tag" << ":" << "start to log");
	char buffer[] = { 0x12,0x13 };
	LOGD("hex data" << ":" << Log4zBinary(buffer, sizeof(buffer)));

	SurrealMemMgr::MemMgr &memmgr= SurrealMemMgr::MemMgr::GetInstance();
	memmgr.SetDebug2File(true);
	STu8 *p1=memmgr.CommonAlloc(SurrealMemMgr::TypeSGIAllocTAlloc, 100);
	STu8 *p2 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIHeapAllocTAlloc, 200);
	STu8 *p3 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIMTAllocatorAlloc, 200);
	STu8 *p4 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIVirtualAllocTAlloc, 200);

	CHttpMaker maker;
	maker.add_param("1", "2");
	return 0;
}