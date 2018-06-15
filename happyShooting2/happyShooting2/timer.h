#pragma once
#include "PCH.h"

namespace timer{
	class timer {
	public:
		static timer* get() {
			return s_pInstance;
		};
		static void Create();
		static void Destroy();
	private:
		static timer* s_pInstance;
	};
}
