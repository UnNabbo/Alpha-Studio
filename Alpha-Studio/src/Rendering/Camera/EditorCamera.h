#pragma once

#include "Camera.h"

#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"

namespace Alpha {
	class EditorCamera : public Camera {
	public:
		EditorCamera();
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);
		~EditorCamera() = default;

		void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);
		void UpdateProjection();

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		glm::quat GetOrientation() const;
		inline const glm::vec3& GetPosition() const { return m_Position; }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		inline const float& GetFOV() { return m_FOV; }
		inline void setFOV(float fov) { m_FOV = fov; }

		void OnUpdate();
		void OnEvent(Event& e);

		void setOrthographic(bool state);

		inline virtual const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }


	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

		void UpdateView();

		std::pair<float, float> PanSpeed() const;

		glm::vec2 GetMouseDelta();

	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.77778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
		glm::mat4 m_Projection = glm::mat4(1);
		glm::mat4 m_ViewMatrix = glm::mat4(1);

		bool m_RotationLock = false;

		glm::vec3 m_Position{ 0.0f, 0.0f, 10.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};
}