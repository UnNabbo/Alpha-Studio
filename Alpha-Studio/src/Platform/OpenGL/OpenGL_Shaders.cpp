#include "OpenGL_Shaders.h"

#include "glad/glad.h"

namespace Alpha {
	namespace Utils {
		static GLenum ShaderStagerToGLenum(uint32_t stage) {
			switch (stage){
			case 0: return GL_VERTEX_SHADER;
			case 1: return GL_FRAGMENT_SHADER;
			}
		}
	}

	OpenGL_Shader::OpenGL_Shader(std::string Path) : m_Path(Path) {
		SetPath(Path);
		m_SPIRV = Compile(Path);

		CreateProgram();
		Bind();
	}

	void OpenGL_Shader::CreateProgram(){
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_SPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(Utils::ShaderStagerToGLenum(stage)));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_ID = program;
	}
	void OpenGL_Shader::Bind() const{
		glUseProgram(m_ID);
	}

	void OpenGL_Shader::Unbind() const{
		glUseProgram(0);
	}

	void OpenGL_Shader::Reload(){
		ALPHA_INFO("RELOAD");

		m_SPIRV = Compile(m_Path, true);

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_SPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(Utils::ShaderStagerToGLenum(stage)));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(m_ID, shaderID);
		}

		glLinkProgram(m_ID);

		GLint isLinked;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ID, maxLength, &maxLength, infoLog.data());

			glDeleteProgram(m_ID);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(m_ID, id);
			glDeleteShader(id);
		}
		glUseProgram(m_ID);

	}
}