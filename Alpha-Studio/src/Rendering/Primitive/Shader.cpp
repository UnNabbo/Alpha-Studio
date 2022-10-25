#include "Shader.h"

#include "Rendering/RendererCommand.h"

#include "Platform/OpenGL/OpenGL_Shaders.h"

#include "shaderc/shaderc.hpp"
#include <fstream>
#include <filesystem>
#include <cstring>

#include "Asset/AssetManager.h"

namespace Alpha {
	namespace Utils {
		static shaderc_shader_kind GLShaderStageToShaderC(ShaderStages stage)
		{	
			switch (RendererCommand::GetCurrentAPI()){
				case OpenGL: {
					switch (stage)
					{
					case Vertex:   return shaderc_glsl_vertex_shader;
					case Pixel: return shaderc_glsl_fragment_shader;
					}
				}
			}
			

			return (shaderc_shader_kind)0;
		}


		static const char* CachedFileExtension(uint32_t stage)
		{
			switch (RendererCommand::GetCurrentAPI()) {
				case OpenGL: {
					switch (stage)
					{
					case Vertex:   return ".cached_opengl.vert";
					case Pixel: return ".cached_opengl.frag";
					}
				}
			}
		}

		static ShaderStages ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return Vertex;
			if (type == "fragment" || type == "pixel")
				return Pixel;

			ALPHA_ASSERT(false, "Unknown shader type!");
		}
	}


	Reference<Shader> Shader::Create(std::string FragPath)
	{
		auto res = AssetManager::Retrive<Shader>(FragPath);
		if (!res.get()) {
			res = AssetManager::CreateAsset<OpenGL_Shader>(FragPath);
	
		}

		return res;
	}

	std::unordered_map<ShaderStages, std::vector<uint32_t>> Shader::Compile(std::string path, bool overwrite) {
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::string name = path.substr(path.find_last_of("/"), path.find_last_of("."));;
		std::filesystem::path cacheDirectory = "asset/shaders/cache/OpenGL";
		
		std::unordered_map<ShaderStages, std::vector<uint32_t>> shaderData;

		std::vector<ShaderStages> stages = { Vertex, Pixel };
		for (auto stage : stages) {
			std::filesystem::path cachedPath = cacheDirectory.string() + (name + Utils::CachedFileExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);

			if (in.is_open() && !overwrite)
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else {

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
				}

				std::string ProcessedSource;

				const char* typeToken = "#type";
				size_t typeTokenLength = strlen(typeToken);
				size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
				while (pos != std::string::npos)
				{
					size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
					//ALPHA_ASSERT(eol != std::string::npos, "Syntax error");
					size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
					std::string type = source.substr(begin, eol - begin);

					size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
					//ALPHA_ASSERT(nextLinePos != std::string::npos, "Syntax error");
					pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

					if (Utils::ShaderTypeFromString(type) == stage) {
						ProcessedSource = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
					}
				}


				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(ProcessedSource, Utils::GLShaderStageToShaderC(stage), path.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					ALPHA_FATAL("{}", module.GetErrorMessage());
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
		return shaderData;
	}
}