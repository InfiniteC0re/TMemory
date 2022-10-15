#pragma once

namespace Toshi
{
	class T2Mutex
	{
	public:
		T2Mutex() = default;

		int Create();

	private:
		void* m_Mutex;
	};
}