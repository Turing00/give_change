------------------------------
-- [ LOCAL VAR DEFINITION ] --
------------------------------

local ROOT = "./"
local srcDir = ROOT .. "src/"
local project_action = "UNDEFINED"

---------------------------------
-- [ WORKSPACE CONFIGURATION ] --
---------------------------------

workspace "give_change"                      -- solution name
  configurations { "Debug", "Release" }      -- non-optimize vs optimize mode
  platforms      { "x32" }                   -- x32 platform

  -- _ACTION is the argument you passed into premake5 when you ran it.
  if _ACTION ~= nil then
    project_action = _ACTION
  end

  -- Where the project files (vs project, solution, etc) go
  location( ROOT .. "project_" .. project_action )

  ----------------------------------
  --  [ COMPILER/LINKER CONFIG ]  --
  ----------------------------------
  filter "configurations:Debug"
    -- Add the preprocessor definition DEBUG to debug builds
    defines { "DEBUG" }
    -- Ensure symbols are bundled with debug builds
    symbols "On"
  
  filter "configurations:Release"
    -- Add the preprocessor definition RELEASE to release builds
    defines { "RELEASE" }
    -- Turn on compiler optimizations for release builds
    optimize "On"

  filter { "platforms:*32" }
    architecture "x32"

  filter { "action:gmake" }
    -- Get that C++14 goodness
    cppdialect "C++14"

  filter { }

  ---------------------------------
  --  [ PROJECT CONFIGURATION ]  --
  ---------------------------------

  -- give_change
  project "give_change"
    kind "ConsoleApp"
    -- Use C++ as the target language for build
    language "C++"

    -- Here we use some "tokens" (the things between %{ ... }).
    -- * %{cfg.buildcfg} will be replaced by "Debug" or "Release" depending on the configuration
    -- * %{cfg.platform} will be replaced by "x32" depending on the configuration
    -- The path is relative to *this* folder
    targetdir ( ROOT .. "bin_%{cfg.buildcfg}_%{cfg.platform}" )

    --------------------------------------
    -- [ PROJECT FILES CONFIGURATIONS ] --
    --------------------------------------

    -- recursively glob .cpp files in the src directory
    files { srcDir .. "**.cpp" }