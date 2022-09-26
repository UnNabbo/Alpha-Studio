workspace "Alpha Studio"
    architecture "x64"
    startproject "Sandbox"

    filter "system:Windows"
      systemversion "latest"
      
    configurations{
        "Debug",
        "Release",
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Alpha-Studio/vendor/glfw/include"
    IncludeDir["Glad"] = "Alpha-Studio/vendor/glad/include"


    include "Alpha-Studio/vendor/GLFW"
    include "Alpha-Studio/vendor/Glad"
    

    project "Alpha-Studio"
        location "Alpha-Studio"
        kind "StaticLib"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"

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
        }

        links{
            "GLFW",
            "Glad",
        }

        defines{
		    "_CRT_SECURE_NO_WARNINGS"
	    }

            

        filter "system:windows"
            systemversion "latest"
        
            defines{
                "BL_PLATFORM_WINDOWS",
                "BLAST_CORE",
                "GLFW_INCLUDE_NONE"
            }

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"

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
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines{
                "BL_PLATFORM_WINDOWS",
                "GLFW_INCLUDE_NONE"
            }