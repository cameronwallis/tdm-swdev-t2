solution "swdevt2"
  configurations { "Debug", "Release" }

project "ercalc"
  kind "ConsoleApp"
  language "C++"
  includedirs { "include" }
  links { "ncurses", "boost_program_options" }
  files { "src/**.hpp", "src/**.cpp" }

  configuration "Debug"
    symbols "On"
    defines { "_DEBUG" }

  configuration "Release"
    flags { "Optimize" }
    defines { "NDEBUG" }