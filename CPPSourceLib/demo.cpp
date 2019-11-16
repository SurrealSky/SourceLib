#include"demo.h"


int main()
{
	SurrealMemMgr::MemMgr &memmgr= SurrealMemMgr::MemMgr::GetInstance();
	STu8 *p1=memmgr.CommonAlloc(SurrealMemMgr::TypeSGIAllocTAlloc, 100);
	STu8 *p2 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIHeapAllocTAlloc, 200);
	STu8 *p3 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIMTAllocatorAlloc, 200);
	STu8 *p4 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIVirtualAllocTAlloc, 200);

	CHttpMaker maker;
	maker.add_param("1", "2");
	return 0;
}