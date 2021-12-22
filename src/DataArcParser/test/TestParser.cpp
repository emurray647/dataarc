#include <iostream>
#include <sstream>
#include "codegen/cpp/CppHeaderGenerator.h"
#include "codegen/cpp/CppSourceGenerator.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"


const std::string TEST_STRING =
"import \"OtherFile.idl\"\n\n"
"package A.B;\n\n"
"enum EyeColor {\n"
"	BLUE,\n"
"	BROWN,\n"
"	GREEN\n"
"}\n\n"
"message Person[22]{\n"
"	uint64 personID;\n"
"	string name;\n"
"	uint32 age;\n"
"	EyeColor eyeColor;\n"
"	// comment\n"
"	double heightInches;\n"
"}\n";



int main(int argc, char** argv) {

	std::stringstream strm;
	strm << TEST_STRING;

	Lexer lexer(strm);
	auto tokens = lexer.Tokenize();
	//for (auto& token : tokens) {
	//	std::cout << token.text << ":  " << (int)token.type << ",  " << 
	//		token.line_number << ":" << token.column_number << std::endl;
	//}

	Parser parser(tokens);
	MessageSet messageSet;
	try {
		messageSet = parser.Parse();
	}
	catch (const ParseException& exp) {
		std::cout << exp.what() << std::endl;
	}

	std::cout << "Done" << std::endl;
	messageSet.SetFileName("test.daidl");

	CodeGenStream stream;
	CppHeaderGenerator headerGenerator(stream);
	headerGenerator.Generate(messageSet);
	std::cout << "Output: " << std::endl;
	std::cout << stream.str() << std::endl;

	CodeGenStream sourceStream;
	CppSourceGenerator sourceGenerator(sourceStream);
	sourceGenerator.Generate(messageSet);
	std::cout << "Source: " << std::endl;
	std::cout << sourceStream.str() << std::endl;

}