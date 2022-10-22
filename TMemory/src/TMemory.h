#pragma once
#include "T2Mutex.h"
#include <cstdint>

#define TASSERT(x, str, ...)
#define BITFIELD(x) (1 << (x))

namespace Toshi
{
	class TMemoryHeap
	{
	public:
		typedef uint32_t Flags;
		enum Flags_ : Flags
		{
			Flags_UseMutex = BITFIELD(0),
			Flags_AllocAsPile = BITFIELD(2),
		};

		friend class TMemory;

	public:
		void* Alloc(size_t size);
		void LogError(size_t size);

		inline void* Data() { return static_cast<void*>(this + 1); }

	private:
		Flags m_Flags;
		uint32_t m_Unk1;
		uint32_t m_Unk2;
		uint32_t m_Size;
		uint32_t m_Unk4;
		uint32_t m_Unk5;
		const char* m_Name;
		uint32_t m_Unk6;
		uint32_t m_Unk7;
		uint32_t m_Unk8;
	};

	class TMemory_Context
	{
	private:
		typedef void* (*t_Malloc)(size_t size);
		typedef void* (*t_Calloc)(size_t nitems, size_t size);
		typedef void* (*t_Realloc)(void* ptr, size_t size);
		typedef void  (*t_Idk)(void* ptr, size_t size);     // it's not even used
		typedef void* (*t_Malloc2)(void* unk, size_t size); // same t_Malloc but 2 arguments
		typedef void  (*t_Free)(void* ptr); 

	public:
		static t_Malloc s_Malloc;
		static t_Calloc s_Calloc;
		static t_Realloc s_Realloc;
		static t_Idk s_Idk;
		static t_Malloc2 s_Malloc2;
		static t_Free s_Free;

		static void* s_Sysheap;
		static void* s_Heap;
		static TMemoryHeap* s_GlobalHeap;
		static T2Mutex s_Mutex;
	};
	
	class TMemory
	{
	public:
		typedef uint32_t Flags;
		typedef uint32_t Error;
		typedef uint32_t BlockSize;

		enum Flags_ : Flags
		{
			Flags_None          = 0,
			Flags_NativeMethods = BITFIELD(1)
		};

		enum Error_ : Error
		{
			Error_Ok   = 0,
			Error_Heap = 1
		};

	public:
		TMemory(Flags flags = Flags_None, BlockSize blockSize = 0x28000000) :
			m_Flags(flags), m_GlobalSize(blockSize) { }

		static int RetrieveSystemInfo();
		static size_t IDK(void* ptr, size_t size);
		static TMemoryHeap* AllocMem(void* ptr, size_t heapSize, TMemoryHeap::Flags flags, const char* name);

		inline static void LockMutex()   { TMemory_Context::s_Mutex.Lock(Flags_None); }
		inline static void UnlockMutex() { TMemory_Context::s_Mutex.Unlock(); }

	public:
		/*
		* Platform specific methods
		* Define them in TMemory_{Platform}.cpp
		*/

		Error Initialize();

	private:
		Flags m_Flags;
		BlockSize m_GlobalSize;
	};

	static void* alloc()
	{

	}
}