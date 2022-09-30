#pragma once

#include "Core/Core.h"

namespace Alpha {
	class Shader {
		static Reference<Shader> Create(const char* name, const char* vertex_path, const char* fragment_path);
		static Reference<Shader> Create(const char* path);

		virtual std::string GetName() const = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Reload() = 0;


		virtual void UploadUniform(std::string name, int* data, uint32_t size) = 0;
	};
}