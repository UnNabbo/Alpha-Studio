workspace "Alpha Studio"
    architecture "x64"
    startproject "Sandbox"

    filter "system:windows"
      systemversion "latest"


    configurations{
        "Debug",
        "Release",
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Alpha-Studio/vendor/glfw/include"
    IncludeDir["Glad"] = "Alpha-Studio/vendor/glad/include"
    IncludeDir["glm"] = "Alpha-Studio/vendor/glm"
    IncludeDir["Vulkan"] = "Alpha-Studio/vendor/vulkan/include"



    include "Alpha-Studio/vendor"

    project "Alpha-Studio"
        location "Alpha-Studio"
        kind "StaticLib"
        staticruntime "on"
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
            "%{IncludeDir.Vulkan}",

        }

        links{
            "GLFW",
            "Glad",
            "Alpha-Studio/vendor/vulkan/lib/vulkan-1.lib"
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

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        staticruntime "on"
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
            staticruntime "On"
            systemversion "latest"

            defines{
                "PLATFORM_WINDOWS",
                "GLFW_INCLUDE_NONE"
            }

        filter "system:linux"
            cppdialect "C++20"
            staticruntime "On"
            systemversion "latest"

            defines{
                "PLATFORM_LINUX",
                "GLFW_INCLUDE_NONE"
            }