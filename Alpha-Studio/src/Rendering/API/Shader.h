#pragma once

#include "Core/Core.h"

#include <unordered_map>

#include "Asset/Resource.h"

namespace Alpha {
	enum ShaderStages {
		Vertex = 0,
		Pixel = 1,
	};


	class Shader : public Resource {
	public:
		static Reference<Shader> Create(std::string FragPath);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Reload() = 0;

	protected:
		
		static std::unordered_map<ShaderStages, std::vector<uint32_t>> Compile(std::string path, bool overwrite = false);
		//static void Reflect(uint32_t stage, std::vector<uint32_t> data);

	};
}