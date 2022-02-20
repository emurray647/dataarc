
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# generate executable
add_executable(DataArcParser
	main.cpp 
	"parser/Lexer.cpp" 
	"parser/Parser.cpp"
	types/MessageSet.cpp 
	"codegen/CodeGenUtils.cpp"
	"codegen/CodeGenStream.cpp" 
	"CommandLineArguments.cpp" 
	"codegen/cpp/CppHeaderGenerator.cpp" 
	"codegen/cpp/CppSourceGenerator.cpp" 
	"codegen/cpp/CppCodeGenUtils.cpp" 
	"codegen/cpp/CppGenerator.cpp"

		# "codegen/CodeGenerator.h" 
	# "codegen/LanguageGenerator.h" 
	# "CommandLineArguments.h" 
		# "codegen/cpp/CppGenerator.h" 
	#"codegen/cpp/CppHeaderGenerator.h" 
	# "codegen/CodeGenStream.h"  
	# "codegen/cpp/CppSourceGenerator.h" 
	# "codegen/cpp/CppCodeGenUtils.h" 
	)