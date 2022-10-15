#include "TMemory.h"

namespace Toshi
{
	TMemory_Context::t_Malloc TMemory_Context::s_Malloc  = nullptr;
	TMemory_Context::t_Calloc TMemory_Context::s_Calloc  = nullptr;
	TMemory_Context::t_Realloc TMemory_Context::s_Realloc = nullptr;
	TMemory_Context::t_Idk TMemory_Context::s_Idk     = nullptr;
	TMemory_Context::t_Malloc2 TMemory_Context::s_Malloc2 = nullptr;
	TMemory_Context::t_Free TMemory_Context::s_Free    = nullptr;

	void* TMemory_Context::s_Sysheap = nullptr;
	void* TMemory_Context::s_Heap = nullptr;
	void* TMemory_Context::s_GlobalBlock = nullptr;
	T2Mutex TMemory_Context::s_Mutex = T2Mutex();
}