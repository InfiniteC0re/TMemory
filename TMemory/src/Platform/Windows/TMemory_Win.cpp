#include "TMemory.h"
#include <Windows.h>

namespace Toshi
{	
	TMemory::Error TMemory::Initialize()
	{
		TASSERT(TMemory_Context::s_Sysheap == NULL, "TMemory is already initialized");
		
		TMemory_Context::s_Mutex.Create();
		TMemory_Context::s_Sysheap = GetProcessHeap();

		if (TMemory_Context::s_Sysheap == NULL)
		{
			return Error_Heap;
		}

		// check if we should use default memory management methods
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

		// allocate memory for the heap
		TMemory_Context::s_Heap = HeapAlloc(TMemory_Context::s_Sysheap, NULL, m_GlobalSize);

		// Save pointers to our own functions
		if (TMemory_Context::s_Heap == NULL)
		{
			return Error_Heap;
		}

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
}