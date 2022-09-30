#pragma once

#include "Core/Core.h"

#include "Core/Window/Window.h"

struct GLFWwindow;

namespace Alpha {

	class Unix_Window : public Window {
	public:
		Unix_Window(WindowData data);
		virtual ~Unix_Window() ;

		inline virtual uint32_t GetHeight() const override { return m_Data.Height; }
		inline virtual uint32_t GetWidth() const override { return m_Data.Width; }

		inline virtual void* GetNative() const override { return m_NativeWindow; }

		virtual void SetCurrent() const override;
		virtual void NewFrame() override;

		virtual bool ShouldClose() const override;

		void Init();
		void ShutDown();
		
	private:
		WindowData m_Data;

		GLFWwindow* m_NativeWindow = 0;
	};
}