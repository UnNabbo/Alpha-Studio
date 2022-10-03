#include "Shader.h"

#include "Rendering/Renderer.h"

#include "Platform/OpenGL/OpenGL_Shaders.h"

#include "shaderc/shaderc.hpp"
#include <fstream>
#include <filesystem>

namespace Alpha {
	namespace Utils {
		static shaderc_shader_kind GLShaderStageToShaderC(ShaderStages stage)
		{	
			switch (Renderer::GetCurrentAPI()){
				case OpenGL: {
					switch (stage)
					{
					case Pixel:   return shaderc_glsl_vertex_shader;
					case Fragment: return shaderc_glsl_fragment_shader;
					}
				}
			}
			

			return (shaderc_shader_kind)0;
		}


		static const char* CachedFileExtension(uint32_t stage)
		{
			switch (Renderer::GetCurrentAPI()) {
				case OpenGL: {
					switch (stage)
					{
					case Pixel:   return ".cached_opengl.vert";
					case Fragment: return ".cached_opengl.frag";
					}
				}
			}
		}
	}


	Reference<Shader> Shader::Create(std::string FragPath, std::string PixelPath)
	{
		return MakeReference<OpenGL_Shader>(FragPath, PixelPath);
	}

	void Shader::Compile(std::string path, ShaderStages stage, std::vector<uint32_t>& shaderData) {
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::string name = path.substr(path.find_last_of("/"), path.find_last_of("."));;
		std::filesystem::path cacheDirectory = "asset/shaders/cache/OpenGL";

		std::filesystem::path cachedPath = cacheDirectory.string() + (name + Utils::CachedFileExtension(stage));

		std::ifstream in(cachedPath, std::ios::in | std::ios::binary);

		if (in.is_open())
		{
			in.seekg(0, std::ios::end);
			auto size = in.tellg();
			in.seekg(0, std::ios::beg);

			auto& data = shaderData;
			data.resize(size / sizeof(uint32_t));
			in.read((char*)data.data(), size);
		}
		else
		{
			std::string source;
			std::ifstream in(path, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
			if (in)
			{
				in.seekg(0, std::ios::end);
				size_t size = in.tellg();
				if (size != -1)
				{
					source.resize(size);
					in.seekg(0, std::ios::beg);
					in.read(&source[0], size);
				}

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), path.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					ALPHA_ASSERT(false, "{}", module.GetErrorMessage());
				}

				shaderData = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData;
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
	
		}

	}
}