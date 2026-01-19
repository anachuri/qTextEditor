# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/qTextEditor_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/qTextEditor_autogen.dir/ParseCache.txt"
  "qTextEditor_autogen"
  )
endif()
