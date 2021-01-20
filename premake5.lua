workspace "XWindowPlayground"
    location "Generated"
    architecture "x86_64"
    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

    filter {}

    targetdir ("Build/bin/%{prj.name}/%{cfg.longname}")
    objdir ("Build/obj/%{prj.name}/%{cfg.longname}")

    project "XWindowLib"
        language "C++"
        kind "StaticLib"
        files {
            "Projects/%{prj.name}/src/**.h",
            "Projects/%{prj.name}/src/**.cpp"
        }
        defines { "XLIB_ILLEGAL_ACCESS" }

        includedirs { "Projects/XWindowLib/src" }

        links {"X11"}

    project "App"
        language "C++"
        kind "WindowedApp"
        files {
            "Projects/%{prj.name}/src/**.h",
            "Projects/%{prj.name}/src/**.cpp"
        }

        includedirs {
            "Projects/XWindowLib/src"
        }

        links {"XWindowLib"}
        links {"X11"}
        