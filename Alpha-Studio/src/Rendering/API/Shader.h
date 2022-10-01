#pragma once

#include "Core/Core.h"

#include <unordered_map>

namespace Alpha {
	enum ShaderStages {
		Fragment = 0,
		Pixel = 1,
	};


	class Shader {
	public:
		static Reference<Shader> Create(std::string FragPath, std::string PixelPath);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Reload() = 0;

	protected:
		
		static void Compile(std::string Sources, ShaderStages stage, std::vector<uint32_t>& data);
		//static void Reflect(uint32_t stage, std::vector<uint32_t> data);

	};
}