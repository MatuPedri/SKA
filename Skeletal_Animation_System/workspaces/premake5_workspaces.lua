project "01_window"

    kind "ConsoleApp"
    language "C++"

    targetdir "../build/%{prj.name}/%{cfg.buildcfg}"
    debugdir "../build/%{prj.name}/%{cfg.buildcfg}"

    includedirs {
        "../engine/core",
        "../engine/include",
		
        "../engine/vendors/stb_image",
        "../engine/vendors/imgui",
        "../engine/vendors/imgui/backends"
    }

    links {
        "skeletal_animation_engine"
    }

    dependson {
        "skeletal_animation_engine"
    }

    conan_config_exec()

    files {
        "01_window/01_window.cpp"
    }

    postbuildcommands {
        "call ..\\tools\\copy_assets.bat \"%{cfg.targetdir}\""
    }