project "skeletal_animation_engine"

    kind "StaticLib"
    language "C++"

    targetdir "../build/%{prj.name}/%{cfg.buildcfg}"
    targetname "skeletal_animation_engine"

    includedirs {
        "core",
        "include",
        "src"
    }

    externalincludedirs {
        "vendors/stb_image",
        "vendors/imgui",
        "vendors/imgui/backends"
    }

    conan_config_lib()

    files {
        "premake5_engine.lua",

        "core/**.cpp",
        "core/**.hpp",
        "core/**.h",

        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
        "include/**.hpp",
        "include/**.h",

        "vendors/stb_image/stb_impl.cpp",

        "vendors/imgui/*.cpp",
        "vendors/imgui/backends/imgui_impl_glfw.cpp",
        "vendors/imgui/backends/imgui_impl_opengl3.cpp",

        "../assets/shaders/**.vs",
        "../assets/shaders/**.fs",
        "../assets/shaders/**.vert",
        "../assets/shaders/**.frag"
    }