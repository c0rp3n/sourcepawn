workspace "sourcepawn"
    platforms { "x86", "x64" }
    configurations { "Debug", "Release" }

    language "C++"
    cppdialect "C++17"

    filter { "platforms:x86" }
        architecture "x86"

    filter { "platforms:x64" }
        architecture "x64"

    filter { "configurations:Debug" }
        defines { "DEBUG", "TRACE" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "Speed"
    
    filter {}

    newoption {
        trigger     = "build",
        value       = "option",
        description = "Which components to build",
        allowed = {
            { "all",    "Build All" },
            { "spcomp",  "Sourcepawn Compiler" },
            { "vm",  "Sp Virtual Machine" },
            { "exp",  "Exp" },
            { "test",  "Tests" },
            { "core",  "Core" }
        },
        default = "all"
    }

    newoption {
        trigger = "amtl",
        value = "path",
        description = "Location of the amtl library",
        default = "./third_party/amtl"
    }

    newoption {
        trigger = "zlib",
        value = "path",
        description = "Location of the zlib library",
        default = "./third_party"
    }

project "libsmx"
    targetdir "build/lib/%{cfg.platform}"
    objdir "build"

    kind "StaticLib"

    includedirs {
        _OPTIONS["amtl"],
        "./include",
        "./"
    }

    files {
        "libsmx/*.cpp",
        "libsmx/*.h",
    }

project "zlib"
    targetdir "build/lib/%{cfg.platform}"
    objdir "build"

    kind "StaticLib"

    files {
        "third_party/zlib/*.c",
        "third_party/zlib/*.h",
    }

project "compiler"
    filter { "platforms:x86" }
        targetname "spcomp"

    filter { "platforms:x64" }
        targetname "spcomp64"

    filter {}

    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build"

    kind "ConsoleApp"

    includedirs {
        _OPTIONS["amtl"],
        _OPTIONS["zlib"],
        "./include",
        "./libsmx",
        "./shared",
        "./"
    }

    files {
        "compiler/*.cpp",
        "compiler/*.h"
    }

    filter { "platforms:x86" }
        libdirs { "build/lib/x86" }

    filter { "platforms:x64" }
        libdirs { "build/lib/x64" }

    filter {}

    links {
        "libsmx",
        "zlib"
    }

    defines {
        "HAVE_STDINT_H",
        'SOURCEPAWN_VERSION="1.10"'
    }
        