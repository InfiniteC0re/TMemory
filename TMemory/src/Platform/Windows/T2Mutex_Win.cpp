#include "T2Mutex.h"
#include <Windows.h>

#define TASSERT(x, str, ...)

namespace Toshi
{
	int T2Mutex::Create()
	{
		m_Mutex = CreateMutexA(NULL, FALSE, NULL);
		TASSERT(m_Mutex != NULL, "Failed to create mutex");
		return 1;
	}
}