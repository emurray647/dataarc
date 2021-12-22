
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# generate executable
add_executable(DataArcParser
	main.cpp 
	"parser/Lexer.cpp" 
	"parser/Parser.cpp"
	types/MessageSet.cpp 
	"codegen/CodeGenerator.h" 
	"codegen/LanguageGenerator.h" 
	"CommandLineArguments.h" 
	"CommandLineArguments.cpp" 
	"codegen/cpp/CppGenerator.h" 
	#"codegen/cpp/CppHeaderGenerator.h" 
	"codegen/cpp/CppHeaderGenerator.cpp" 
	"codegen/CodeGenStream.h"  "codegen/CodeGenStream.cpp" "codegen/cpp/CppSourceGenerator.h" "codegen/cpp/CppSourceGenerator.cpp" "codegen/cpp/CppCodeGenUtils.h" "codegen/cpp/CppCodeGenUtils.cpp" "codegen/cpp/CppGenerator.cpp")