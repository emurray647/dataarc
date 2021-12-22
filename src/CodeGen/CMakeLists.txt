# CMakeList.txt : CMake project for CodeGen, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (CodeGen "CodeGen.cpp" "CodeGen.h"  "include/dataarc/codegen/types/Class.h" "include/dataarc/codegen/types/Field.h" "include/dataarc/codegen/types/DataType.h")

# TODO: Add tests and install targets if needed.
