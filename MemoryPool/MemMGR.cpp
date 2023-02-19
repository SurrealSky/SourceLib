#include"stdafx.h"
#include"MemMgr.h"
#include"MemManager.h"
#include<Lock.h>
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

using namespace SurrealMemMgr;


MemMgr &MemMgr::GetInstance()
{
	AutoLock lock;
	static MemMgr instance;
	instance.isDebug2File = false;
	return instance;
}



MemMgr::MemMgr()
{
	pImpl = new MemManager();
	if (isDebug2File)
	{
		SurrealDebugLog::DebugLog("MemManager", "init");
	}
}

MemMgr::~MemMgr()
{
	if (pImpl)
	{
		delete pImpl;
		pImpl = NULL;
	}
	if (isDebug2File)
		SurrealDebugLog::DebugLog("MemManager","destory");
}

void MemMgr::SetDebug2File(bool b)
{
	isDebug2File = b;
}

const MemMgr &MemMgr::operator=(const MemMgr &m)
{
	if (pImpl)
	{
		delete pImpl;
	}
	pImpl = new MemManager(*m.pImpl);
	return *this;
}

MemMgr::MemMgr(const MemMgr &m)
{
	if (pImpl)
	{
		delete pImpl;
	}
	pImpl = new MemManager(*m.pImpl);
}

STu8* MemMgr::CommonAlloc(const MemAllocType _type,const STu64 Size)
{
	STu8 *pointer= (STu8*)pImpl->CommonAlloc(_type, Size);
	if (isDebug2File)
		SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemAlloc=%02X,address=0x%08X,size=0x%X","CommonAlloc", _type, pointer,Size));
	return pointer;
}

void MemMgr::CommonDeallocate(const MemAllocType _type, STu8 *p, const STu64 Size)
{
	if (isDebug2File)
		SurrealDebugLog::DebugLog(SurrealDebugLog::string_format("%s:MemFree=%02X,address=0x%08X,size=%X","CommonAlloc", _type, p,Size));
	return pImpl->CommonDeallocate(_type,(char*)p, Size);
}