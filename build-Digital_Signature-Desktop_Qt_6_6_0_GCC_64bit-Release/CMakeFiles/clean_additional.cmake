# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/Digital_Signature_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Digital_Signature_autogen.dir/ParseCache.txt"
  "Digital_Signature_autogen"
  )
endif()
