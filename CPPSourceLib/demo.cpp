#include"demo.h"

int main()
{
	CLock lock;
	SurrealMemMgr::MemMgr memmgr;
	STu8 *p1=memmgr.CommonAlloc(SurrealMemMgr::TypeSGIAllocTAlloc, 100);
	STu8 *p2 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIHeapAllocTAlloc, 200);
	STu8 *p3 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIMTAllocatorAlloc, 200);
	STu8 *p4 = memmgr.CommonAlloc(SurrealMemMgr::TypeSGIVirtualAllocTAlloc, 200);

	return 0;
}