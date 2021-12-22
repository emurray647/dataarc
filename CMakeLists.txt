# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("DataArc")

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

# Include sub-projects.
#add_subdirectory("src/CodeGen")
add_subdirectory("src/DataArcParser")
add_subdirectory("src/DataArc")
