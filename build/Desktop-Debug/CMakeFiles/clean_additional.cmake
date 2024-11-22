# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/DuniceDesktop_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DuniceDesktop_autogen.dir/ParseCache.txt"
  "DuniceDesktop_autogen"
  )
endif()
