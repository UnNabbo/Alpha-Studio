#include "Time.h"

#include "Core/Core.h"

namespace Alpha {

	float Time::DeltaTime() {
		m_DeltaTime = m_ElapsedTime - m_LastFrameTime;
		return m_DeltaTime;
	}

	float Time::CurrentTime() {
		return 0.f;
	}

	void Time::Update() {
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = m_TimeStart - end;
		m_LastFrameTime = m_ElapsedTime;
		m_ElapsedTime = -elapsed_seconds.count();

	}

	void Time::Init() {
		m_TimeStart = std::chrono::steady_clock::now();
	}
}