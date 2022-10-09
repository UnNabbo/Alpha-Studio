#pragma once

#include <chrono>

namespace Alpha {
	class Time {
	public:
		static float DeltaTime();
		static float CurrentTime();

		static void Update();
		static void Init();

	private:
		inline static float m_DeltaTime = 0;
		inline static float m_ElapsedTime = 0;
		inline static float m_LastFrameTime= 0;
		inline static std::chrono::steady_clock::time_point m_TimeStart;

	};
}