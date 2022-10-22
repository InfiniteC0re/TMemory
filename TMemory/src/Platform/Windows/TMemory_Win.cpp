#include "TMemory.h"
#include "TUtils.h"

#include <Windows.h>

namespace Toshi
{
	static DWORD s_PageSize = 0;
	static DWORD s_AllocGranularity = 0;
	static DWORD s_Unk1 = 0;
	static DWORD s_Unk2 = 0;
	static DWORD s_Unk3 = 0;
	static DWORD s_Unk4 = 0;
	static DWORD s_Unk5 = 0;

	// 006ffc10
	static void* FUN_006ffc10(void* ptr, size_t size)
	{

	}

	size_t TMemory::IDK(void* ptr, size_t size)
	{
		// 006fcb20
		TMemory::RetrieveSystemInfo();

		if ((0x1f8 < size) && (size < -s_PageSize - 0x1f8)) {
			iVar1 = FUN_006ffc10(data, size);
			*(undefined4*)(iVar1 + 0x1c4) = 8;
			return iVar1;
		}

		return 0;
	}

	int TMemory::RetrieveSystemInfo()
	{
		if (s_PageSize == 0)
		{
			s_Unk1 = 0x200000;
			s_Unk4 = -1;
			s_Unk2 = 4;

			auto seconds = TUtils::GetUnixSeconds();

			if (s_Unk3 == 0)
			{
				s_Unk5 = s_Unk2;
				s_Unk3 = ((uint32_t)seconds ^ 0x55555550) & 0xfffffff8 | 8;
			}

			SYSTEM_INFO info;
			GetSystemInfo(&info);

			s_PageSize = info.dwPageSize;
			s_AllocGranularity = info.dwAllocationGranularity;

			// check the values are power of two
			if (((s_AllocGranularity & s_AllocGranularity - 1) != 0) || ((s_PageSize & s_PageSize - 1) != 0))
			{
				abort();
				return 1;
			}

			return 0;
		}

		return 0;
	}

	TMemory::Error TMemory::Initialize()
	{
		// 0x006fb9d0
		TASSERT(TMemory_Context::s_Sysheap == NULL, "TMemory is already initialized");
		
		TMemory_Context::s_Mutex.Create();
		TMemory_Context::s_Sysheap = GetProcessHeap();

		if (TMemory_Context::s_Sysheap == NULL)
		{
			return Error_Heap;
		}

		// Check if we should use default memory management methods
		if (m_Flags & Flags_NativeMethods)
		{
			TMemory_Context::s_Malloc = [](size_t size) -> void*
			{
				return malloc(size);
			};

			TMemory_Context::s_Calloc = [](size_t nitems, size_t size) -> void*
			{
				return calloc(nitems, size);
			};

			TMemory_Context::s_Realloc = [](void* ptr, size_t size) -> void*
			{
				return realloc(ptr, size);
			};

			TMemory_Context::s_Malloc2 = [](void* unk, size_t size) -> void*
			{
				return malloc(size);
			};

			TMemory_Context::s_Free = [](void* ptr) -> void
			{
				free(ptr);
			};

			TMemory_Context::s_Idk = [](void* ptr, size_t size) -> void
			{

			};

			return Error_Ok;
		}

		// Allocate memory for the heap
		TMemory_Context::s_Heap = HeapAlloc(TMemory_Context::s_Sysheap, NULL, m_GlobalSize);

		// Save pointers to our own functions
		if (TMemory_Context::s_Heap == NULL)
		{
			return Error_Heap;
		}

		TMemory_Context::s_Malloc = [](size_t size) -> void*
		{
			return nullptr;
		};

		TMemory_Context::s_Calloc = [](size_t nitems, size_t size) -> void*
		{
			return nullptr;
		};

		TMemory_Context::s_Realloc = [](void* ptr, size_t size) -> void*
		{
			return nullptr;
		};

		TMemory_Context::s_Malloc2 = [](void* unk, size_t size) -> void*
		{
			return nullptr;
		};

		TMemory_Context::s_Free = [](void* ptr) -> void
		{
			
		};

		TMemory_Context::s_Idk = [](void* ptr, size_t size) -> void
		{

		};

		AllocMem(TMemory_Context::s_Heap, m_GlobalSize, TMemoryHeap::Flags_UseMutex, "global");

		return Error_Ok;
	}
}