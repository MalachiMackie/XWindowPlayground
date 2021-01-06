workspace "XWindowPlayground"
    location "Generated"
    language "C++"
    architecture "x86_64"
    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

    filter {}

    targetdir ("Build/bin/%{prj.name}/%{cfg.longname}")
    objdir ("Build/obj/%{prj.name}/%{cfg.longname}")

    project "App"
        kind "WindowedApp"
        files {
            "Projects/App/**.h",
            "Projects/App/**.cpp"
        }
        
        links {"X11"}


