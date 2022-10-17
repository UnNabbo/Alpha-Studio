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
    LibraryDir["Assimp"] = "Alpha-Studio/vendor/assimp/bin"
    
    Library = {}
    Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
    Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"
    
    Library["Assimp_Debug"] = "D:/DEV/Alpha Studio/Alpha-Studio/vendor/assimp/bin/Debug/assimp-vc143-mtd.lib"
    Library["Zlib"] = "D:/DEV/Alpha Studio/Alpha-Studio/vendor/assimp/contrib/zlib/Debug/zlibstaticd.lib"
    Library["Assimp_Release"] = "D:/DEV/Alpha Studio/Alpha-Studio/vendor/assimp/bin/Release/assimp-vc143-mt.lib"


    Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
    Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
    Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
    Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"
    
    Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
    Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
    Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"


    IncludeDir = {}
    
    IncludeDir["GLFW"] = "Alpha-Studio/vendor/glfw/include"
    IncludeDir["Assimp"] = "Alpha-Studio/vendor/assimp/include/"
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
        language "C++"
        cppdialect "C++20"
        staticruntime "off"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        defines{
            "_CRT_SECURE_NO_WARNINGS",
            "GLFW_INCLUDE_NONE"
        }

        includedirs{
            "%{prj.name}/src",
            "%{prj.name}/vendor",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.VulkanSDK}",
            "%{IncludeDir.Assimp}",
            "%{IncludeDir.Assimp}/include/",
            "%{IncludeDir.Assimp}/code/",
            "%{IncludeDir.Assimp}/contrib/pugixml/src",
        }

        links{
            "GLFW",
            "Glad",
		    "opengl32.lib",
            "%{Library.Zlib}",

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
            runtime "Debug"
            symbols "on"

            links
            {
                "%{Library.Assimp_Debug}",
                "%{Library.ShaderC_Debug}",
                "%{Library.SPIRV_Cross_Debug}",
                "%{Library.SPIRV_Cross_GLSL_Debug}"
            }

	    filter "configurations:Release"
            defines "ALPHA_RELEASE"
            runtime "Release"
            optimize "on"

            links
            {

                "%{Library.Assimp_Release}",
                "%{Library.ShaderC_Release}",
                "%{Library.SPIRV_Cross_Release}",
                "%{Library.SPIRV_Cross_GLSL_Release}"
            }

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"
        linkgroups "On"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs{
            "Alpha-Studio/src",
            "Alpha-Studio/vendor",
            "Alpha-Studio/",  
            "%{IncludeDir.glm}",
        }

        links{
            "GLFW",
            "Glad",
            "Alpha-Studio",

        }

        filter "configurations:Debug"
            defines "ALPHA_DEBUG"
            runtime "Debug"
            symbols "on"
            links
            {
                "%{Library.Assimp_Debug}",
            }
    
        filter "configurations:Release"
            defines "ALPHA_RELEASE"
            runtime "Release"
            optimize "on"

            links
            {

                "%{Library.Assimp_Release}",
            }


