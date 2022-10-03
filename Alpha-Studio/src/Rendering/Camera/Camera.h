#pragma once

#include "glm/glm.hpp"


namespace Alpha {
	class Camera {
	public:
		virtual ~Camera() = default;
		
		virtual const glm::mat4&  GetProjectionMatrix() const = 0;
	};
}