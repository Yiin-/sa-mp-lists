solution "lists"
	configurations { "Release", "Debug" }
	language "C++"

	project "lists"
		includedirs { "lib", "lib/sdk" }
		kind "SharedLib"
		targetprefix ""
		if _ACTION == "gmake" then
			files { "**.c", "**.cpp" }
			links { "rt" }
			targetextension ".so"
		elseif string.startswith(_ACTION, "vs") then
			files { "**.c", "**.cpp", "**.def", "**.rc", "src/**.h" }
			targetextension ".dll"
		end

	configuration "Release"
		if _ACTION == "gmake" then
			buildoptions { "-ffast-math", "-fmerge-all-constants", "-fno-strict-aliasing", "-fPIC", "-fvisibility=hidden", "-fvisibility-inlines-hidden", "-m32", "-O3", "-Wall" }
			defines { "_GNU_SOURCE", "NDEBUG" }
			flags "NoImportLib"
			linkoptions "-m32"
			objdir "obj/linux/Release"
			targetdir "bin/linux/Release"
		elseif string.startswith(_ACTION, "vs") then
			defines { "_CRT_SECURE_NO_WARNINGS", "NDEBUG", "SAMPGDK_AMALGAMATION" }
			flags { "FatalWarnings", "LinkTimeOptimization", "NoBufferSecurityCheck" }
			objdir "obj/win32/Release"
			optimize "Speed"
			targetdir "bin/win32/Release"
		end

	configuration "Debug"
		if _ACTION == "gmake" then
			buildoptions { "-fPIC", "-m32", "-O0", "-Wall" }
			defines { "_GNU_SOURCE" }
			flags { "NoImportLib", "Symbols" }
			linkoptions { "-m32", "-rdynamic" }
			objdir "obj/linux/Debug"
			targetdir "bin/linux/Debug"
		elseif string.startswith(_ACTION, "vs") then
			defines { "_CRT_SECURE_NO_WARNINGS" }
			flags { "FatalWarnings", "Symbols" }
			objdir "obj/win32/Debug"
			targetdir "bin/win32/Debug"
		end