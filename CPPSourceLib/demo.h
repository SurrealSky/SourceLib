#pragma once
//公共
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<typedef.h>
using namespace SurrealTypes;

#include<disasm\disasm.h>
#include<pack\TXCommPack.h>
#include<xml\Markup.h>
#include<CodedConvert.h>
#include<EasySize.h>
#include<Hex.h>
#include<Lock.h>
#include<MiniDump.h>
#include<SimpleIni.h>
#include<http\http_util.h>



//以下为MemoryPool库需要的头文件和库文件（静态编译）
#include"../MemoryPool/MemMgr.h"

#ifdef _DEBUG

#pragma comment(lib,"../debug/MemMgr.lib")

#else

#pragma comment(lib,"../release/MemMgr.lib")

#endif // DEBUG


