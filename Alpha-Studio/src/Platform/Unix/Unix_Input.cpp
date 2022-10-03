#include "Input/Input.h"

#include "GLFW/glfw3.h"

#include "Core/Application.h"
#include "Core/Window/Window.h"

namespace Alpha {
	 bool Input::GetKey(Keycode key){
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());

		 return glfwGetKey(Window, key) != GLFW_RELEASE;
	 }

	 bool Input::GetMouseButton(MouseButton key) {
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());

		 return glfwGetMouseButton(Window, key) != GLFW_RELEASE;
	 }

	 bool Input::GetKeyUp(Keycode key){
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());

		 return glfwGetKey(Window, key) == GLFW_RELEASE;
	 }

	 bool Input::GetMouseButtonUp(MouseButton key){
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());

		 return glfwGetMouseButton(Window, key) == GLFW_RELEASE;
	 }

	 bool Input::GetKeyDown(Keycode key){
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());

		 return glfwGetKey(Window, key) == GLFW_PRESS;
	 }

	 bool Input::GetMouseButtonDown(MouseButton key){
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());

		 return glfwGetMouseButton(Window, key) == GLFW_PRESS;
	 }

	 glm::vec2 Input::GetMousePos() {
		 const auto& Window = static_cast<GLFWwindow*>(Application::GetApp().GetMainWindow()->GetNative());
		 double xpos, ypos;
		 glfwGetCursorPos(Window, &xpos, &ypos);

		 return  { (float)xpos, (float)ypos };
	 }
}