
set(CODE_UNDER_TEST_DIRECTORY "../src")
include_directories(${CODE_UNDER_TEST_DIRECTORY})

message("-------------: " ${CMAKE_CURRENT_BINARY_DIR})
message("######: " ${GTEST_INCLUDE_PATH})

# include_directories(${GTEST_INCLUDE_PATH})
# include_directories(${GMOCK_INCLUDE_PATH})

add_executable(TestParser 
	TestCppGen.cpp
	TestParser.cpp 
	${CODE_UNDER_TEST_DIRECTORY}/parser/Lexer.cpp
	${CODE_UNDER_TEST_DIRECTORY}/parser/Parser.cpp
	${CODE_UNDER_TEST_DIRECTORY}/parser/Program.cpp
	${CODE_UNDER_TEST_DIRECTORY}/types/MessageSet.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/CodeGenStream.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppHeaderGenerator.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppSourceGenerator.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppCodeGenUtils.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppGenerator.cpp
	)

target_include_directories(TestParser PUBLIC ${GTEST_INCLUDE_PATH})
target_include_directories(TestParser PUBLIC ${GMOCK_INCLUDE_PATH})

target_link_libraries(TestParser gtest_main)
target_link_libraries(TestParser gmock_main)

#message("------------------: " ${CMAKE_CURRENT_BINARY_DIR})
#install(FILES test.idl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})