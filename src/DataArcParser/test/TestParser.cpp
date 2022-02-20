#include <iostream>
#include <sstream>
#include "codegen/cpp/CppHeaderGenerator.h"
#include "codegen/cpp/CppSourceGenerator.h"
#include "codegen/go/GoGenerator.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/Program.h"

#include "gtest/gtest.h"

using namespace ::testing;

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

TEST(TestParser, BaseTest) {
	std::stringstream strm;
	strm << TEST_STRING;

	// Lexer lexer(strm);
	// auto tokens = lexer.Tokenize();

	// Parser parser(tokens);
	Program program(strm);
	MessageSet messageSet;
	EXPECT_NO_THROW(messageSet = program.Parse());

	auto& messages = messageSet.GetMessages();
	EXPECT_EQ(1, messages.size());

	// EXPECT_EQ(1, messageSet.GetPackage().packageNames.size());

	auto& fields = messages[0].fields;
	EXPECT_EQ(5, fields.size());

	EXPECT_EQ("personID", fields[0].name);
	EXPECT_EQ(DataType::Type::UINT64, fields[0].type.type);
	EXPECT_FALSE(fields[0].type.isRepeated);

	EXPECT_EQ("name", fields[1].name);
	EXPECT_EQ(DataType::Type::STRING, fields[1].type.type);
	EXPECT_FALSE(fields[1].type.isRepeated);

	EXPECT_EQ("age", fields[2].name);
	EXPECT_EQ(DataType::Type::UINT32, fields[2].type.type);
	EXPECT_FALSE(fields[2].type.isRepeated);

	EXPECT_EQ("eyeColor", fields[3].name);
	EXPECT_EQ(DataType::Type::CUSTOM, fields[3].type.type);
	EXPECT_FALSE(fields[3].type.isRepeated);

	EXPECT_EQ("heightInches", fields[4].name);
	EXPECT_EQ(DataType::Type::DOUBLE, fields[4].type.type);
	EXPECT_FALSE(fields[4].type.isRepeated);

	EXPECT_EQ(1, messageSet.GetImports().size());
	EXPECT_STREQ("OtherFile.idl", messageSet.GetImports()[0].importFileName.c_str());

}

// int main(int argc, char** argv) {

// 	std::stringstream strm;
// 	strm << TEST_STRING;

// 	Lexer lexer(strm);
// 	auto tokens = lexer.Tokenize();
// 	//for (auto& token : tokens) {
// 	//	std::cout << token.text << ":  " << (int)token.type << ",  " << 
// 	//		token.line_number << ":" << token.column_number << std::endl;
// 	//}

// 	Parser parser(tokens);
// 	MessageSet messageSet;
// 	try {
// 		messageSet = parser.Parse();
// 	}
// 	catch (const ParseException& exp) {
// 		std::cout << exp.what() << std::endl;
// 	}

// 	std::cout << "Done" << std::endl;
// 	messageSet.SetFileName("test.daidl");

// 	CodeGenStream stream;
// 	CppHeaderGenerator headerGenerator(stream);
// 	headerGenerator.Generate(messageSet);
// 	std::cout << "Output: " << std::endl;
// 	std::cout << stream.str() << std::endl;

// 	CodeGenStream sourceStream;
// 	CppSourceGenerator sourceGenerator(sourceStream);
// 	sourceGenerator.Generate(messageSet);
// 	std::cout << "Source: " << std::endl;
// 	std::cout << sourceStream.str() << std::endl;

// 	// CodeGenStream goStream;
// 	// GoGenerator goGenerator(goStream);

// }