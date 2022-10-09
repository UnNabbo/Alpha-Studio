#pragma once

#include "Rendering/API/Shader.h"

namespace Alpha {
	class OpenGL_Shader : public Shader {
	public:
		OpenGL_Shader(std::string PixelPath);
		~OpenGL_Shader() = default;

		void CreateProgram();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void Reload() override;
	private:
		uint32_t m_ID;
		std::string m_Path;
		std::unordered_map<ShaderStages, std::vector<uint32_t>> m_SPIRV;
	};
}