#pragma once
//#include<Windows.h>
//#ifdef _USRDLL
//#define MEMORY_EXPORTS 1
//#else
//#undef  MEMORY_EXPORTS
//#endif

#ifdef MEMORY_EXPORTS
#define MEMORYEXPORTS_API __declspec(dllexport)
#else
#define MEMORYEXPORTS_API __declspec(dllimport)
#endif

namespace SurrealMemMgr
{

	//内存分配类型
	enum MemAllocType
	{
		TypeStdAllocTAlloc,
		TypeSGIAllocTAlloc,
		TypeSGIVirtualAllocTAlloc,
		TypeSGIHeapAllocTAlloc,
		TypeSGIMTAllocatorAlloc
	};

	/*MEMORYEXPORTS_API*/char* CommonAlloc(const MemAllocType,const DWORD dwSize);
	/*MEMORYEXPORTS_API*/void CommonDeallocate(const MemAllocType,char *p,const DWORD dwSize=0);

}
