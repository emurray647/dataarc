
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# create our library
add_library(DataArc SHARED
			src/ByteBuffer.cpp "include/Message.h")