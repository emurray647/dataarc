
set(CODE_UNDER_TEST_DIRECTORY "../src")
include_directories(${CODE_UNDER_TEST_DIRECTORY})

add_executable(TestParser 
	TestParser.cpp 
	${CODE_UNDER_TEST_DIRECTORY}/parser/Lexer.cpp
	${CODE_UNDER_TEST_DIRECTORY}/parser/Parser.cpp
	${CODE_UNDER_TEST_DIRECTORY}/types/MessageSet.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/CodeGenStream.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppHeaderGenerator.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppSourceGenerator.cpp
	${CODE_UNDER_TEST_DIRECTORY}/codegen/cpp/CppCodeGenUtils.cpp
	)

#message("------------------: " ${CMAKE_CURRENT_BINARY_DIR})
#install(FILES test.idl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})