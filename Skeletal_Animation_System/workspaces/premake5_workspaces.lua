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
        -- $(TargetDir) is absolute (copy_assets.bat changes directory); trailing "." avoids the "\" escaping the closing quote
        "call ..\\tools\\copy_assets.bat \"$(TargetDir).\""
    }

project "02_triangle"

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
        "02_triangle/02_triangle.cpp"
    }

    postbuildcommands {
        -- $(TargetDir) is absolute (copy_assets.bat changes directory); trailing "." avoids the "\" escaping the closing quote
        "call ..\\tools\\copy_assets.bat \"$(TargetDir).\""
    }

project "03_model_loading"

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
        "03_model_loading/03_model_loading.cpp"
    }

    postbuildcommands {
        -- $(TargetDir) is absolute (copy_assets.bat changes directory); trailing "." avoids the "\" escaping the closing quote
        "call ..\\tools\\copy_assets.bat \"$(TargetDir).\""
    }

project "04_skeletal_animation"

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
        "04_skeletal_animation/04_skeletal_animation.cpp"
    }

    postbuildcommands {
        -- $(TargetDir) is absolute (copy_assets.bat changes directory); trailing "." avoids the "\" escaping the closing quote
        "call ..\\tools\\copy_assets.bat \"$(TargetDir).\""
    }

project "05_skinning_gpu"

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
        "05_skinning_gpu/05_skinning_gpu.cpp"
    }

    postbuildcommands {
        -- $(TargetDir) is absolute (copy_assets.bat changes directory); trailing "." avoids the "\" escaping the closing quote
        "call ..\\tools\\copy_assets.bat \"$(TargetDir).\""
    }