#include"stdafx.h"
#include"MemMgr.h"
#include"MemManager.h"

using namespace SurrealMemMgr;

MemMgr::MemMgr()
{
	pImpl = new MemManager();
}

MemMgr::~MemMgr()
{
	if (pImpl)
	{
		delete pImpl;
		pImpl = 0;
	}
}


STu8* MemMgr::CommonAlloc(const MemAllocType _type,const STu64 dwSize)
{
	return (STu8*)pImpl->CommonAlloc(_type,dwSize);
}
void MemMgr::CommonDeallocate(const MemAllocType _type, STu8 *p, const STu64 Size)
{
	return pImpl->CommonDeallocate(_type,(char*)p, Size);
}