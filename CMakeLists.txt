# CMakeList.txt : CMake project for adventofcode2023, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("adventofcode2023")

# Add source to this project's executable.
add_executable (adventofcode2023 "adventofcode2023.cpp" "adventofcode2023.h" "p1.cpp" "common.h" "p2.cpp" "p3.cpp" "p4.cpp" "common.cpp" "p5.cpp" "p6.cpp" "p7.cpp" "p8.cpp" "p9.cpp" "p10.cpp" "p11.cpp" "p12.cpp" "p13.cpp" "p14.cpp" "p15.cpp" "p16.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET adventofcode2023 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
