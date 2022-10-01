workspace "Alpha Studio"
    architecture "x64"
    startproject "Sandbox"

    filter "system:windows"
      systemversion "latest"


    configurations{
        "Debug",
        "Release",
    }

    flags
	{
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    VULKAN_SDK = os.getenv("VULKAN_SDK")

    LibraryDir = {}

    LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
    
    Library = {}
    Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
    Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"
    
    Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
    Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
    Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
    Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"
    
    Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
    Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
    Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

    IncludeDir = {}
    
    IncludeDir["GLFW"] = "Alpha-Studio/vendor/glfw/include"
    IncludeDir["Glad"] = "Alpha-Studio/vendor/glad/include"
    IncludeDir["glm"] = "Alpha-Studio/vendor/glm"
    IncludeDir["Vulkan"] = "Alpha-Studio/vendor/vulkan/include"

    IncludeDir["shaderc"] = "Alpha-Studio/vendor/shaderc/include"
    IncludeDir["SPIRV_Cross"] = "Alpha-Studio/vendor/SPIRV-Cross"
    IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
    


    include "Alpha-Studio/vendor"

    project "Alpha-Studio"
        location "Alpha-Studio"
        kind "StaticLib"
        staticruntime "off"
        language "C++"
        cppdialect "C++20"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        includedirs{
            "%{prj.name}/src",
            "%{prj.name}/vendor",
            "%{prj.name}/vendor/spdlog/include",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.VulkanSDK}"

        }

        links{
            "GLFW",
            "Glad",
            "%{Library.Vulkan}"
        }

        defines{
		    "_CRT_SECURE_NO_WARNINGS"
	    }

        filter "system:windows"
            systemversion "latest"
        
            defines{
                "PLATFORM_WINDOWS",
                "ALPHA_CORE",
                "GLFW_INCLUDE_NONE"
            }

        filter "system:linux"
    
            defines{
                "PLATFORM_LINUX",
                "ALPHA_CORE",
                "GLFW_INCLUDE_NONE"
            }

        filter "configurations:Debug"
            defines "ALPHA_DEBUG"
            
            links
            {
                "%{Library.ShaderC_Debug}",
                "%{Library.SPIRV_Cross_Debug}",
                "%{Library.SPIRV_Cross_GLSL_Debug}"
            }

	    filter "configurations:Release"
            defines "ALPHA_RELEASE"
            optimize "on"

            links
            {
                "%{Library.ShaderC_Release}",
                "%{Library.SPIRV_Cross_Release}",
                "%{Library.SPIRV_Cross_GLSL_Release}"
            }

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        staticruntime "off"
        language "C++"
        cppdialect "C++20"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs{
            "Alpha-Studio/vendor/spdlog/include",
            "Alpha-Studio/src",
            "Alpha-Studio/vendor",
            "Alpha-Studio/",  

        }

        links{
            "Alpha-Studio"
        }

        filter "system:windows"
            cppdialect "C++20"
            staticruntime "off"
            systemversion "latest"

            defines{
                "PLATFORM_WINDOWS",
                "GLFW_INCLUDE_NONE"
            }

        filter "system:linux"
            cppdialect "C++20"
            staticruntime "off"
            systemversion "latest"

            defines{
                "PLATFORM_LINUX",
                "GLFW_INCLUDE_NONE"
            }