#include "TMemory.h"
#include <iostream>

namespace Toshi
{
	TMemory_Context::t_Malloc TMemory_Context::s_Malloc   = nullptr;
	TMemory_Context::t_Calloc TMemory_Context::s_Calloc   = nullptr;
	TMemory_Context::t_Realloc TMemory_Context::s_Realloc = nullptr;
	TMemory_Context::t_Idk TMemory_Context::s_Idk         = nullptr;
	TMemory_Context::t_Malloc2 TMemory_Context::s_Malloc2 = nullptr;
	TMemory_Context::t_Free TMemory_Context::s_Free       = nullptr;

	void* TMemory_Context::s_Sysheap           = nullptr;
	void* TMemory_Context::s_Heap              = nullptr;
	TMemoryHeap* TMemory_Context::s_GlobalHeap = nullptr;
	T2Mutex TMemory_Context::s_Mutex           = T2Mutex();

	void* TMemoryHeap::Alloc(size_t size)
	{
		// 006fc520

		if (m_Flags & Flags_AllocAsPile)
		{
			// FUN_006fc8b0(this,size,4);
		}

		if (m_Flags & Flags_UseMutex)
		{
			TMemory::LockMutex();
		}

		// FUN_006fcb60(this->m_Unk3,size);

		if (m_Flags & Flags_UseMutex)
		{
			TMemory::UnlockMutex();
		}

		return nullptr;
	}

	void TMemoryHeap::LogError(size_t size)
	{
		// 006fc7c0

		std::cout << "=========================================================================\n";
		std::cout << "MEMORY ALLOCATION FAILED\n";
		std::cout << "------------------------\n";
		std::cout << "HEAP: "  << m_Name  << "\n";
		std::cout << "------------------------\n";
		std::cout << "failed to allocate " << size << " bytes (~" << (size + 0x200 >> 10) << "KB, ~" << (size + 0x80000 >> 0x14) << "MB)\n";
		// FUN_006fbec0(local_e8);
		std::cout << "=========================================================================\n";
		// ...
	}

	TMemoryHeap* TMemory::AllocMem(void* ptr, size_t heapSize, TMemoryHeap::Flags flags, const char* name)
	{
		size_t size = heapSize - sizeof(TMemoryHeap);

		TASSERT(size > 0, "Allocation size is zero");
		TASSERT((size & 3) == 0, "Allocation size is not aligned to 4");
		
		TMemoryHeap* pHeap = static_cast<TMemoryHeap*>(ptr);

		pHeap->m_Unk2 = 0;
		IDK(pHeap + 1, size);

		return nullptr;
	}
}