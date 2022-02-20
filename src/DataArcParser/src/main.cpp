
#include <iostream>
#include <fstream>
#include <filesystem>

#include "CommandLineArguments.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"

#include "codegen/cpp/CppGenerator.h"
#include "codegen/CodeGenUtils.h"

int main(int argc, char** argv) {

	std::cout << "Running" << std::endl;
	/*argv = new char*[5];
	argv[0] = ".\DataArcParser.exe"; 
	argv[1] = "--input";
	argv[2] = "samples";
	argv[3] = "--output-cpp";
	argv[4] = "out";*/

	CommandLineArguments cla;
	cla.Parse(argc, argv);

	std::vector<MessageSet> messageSets;

	for (const std::string& directory : cla.GetInputDirectories()) {
		for (auto& p : std::filesystem::directory_iterator(directory)) {
			std::cout << p.path() << std::endl;

			std::ifstream instream(p.path());
			Lexer lexer(instream);
			auto tokens = lexer.Tokenize();
			Parser parser(tokens);
			MessageSet messageSet;
			try {
				std::cout << "P------: " << p.path().filename().string() << std::endl;
				
				std::cout << messageSet.GetFileName() << std::endl;
				messageSet = parser.Parse();
				messageSet.SetFileName(p.path().filename().string());
				messageSets.push_back(messageSet);
			}
			catch (ParseException& exp) {
				std::cerr << exp.what();
			}

		}
	}

	if (cla.GetOutputCppDirectory() != "") {
		std::filesystem::path directory(cla.GetOutputCppDirectory());
		std::filesystem::create_directory(directory);
		std::cout << "directory: " << directory.string() << std::endl;
		std::cout << messageSets[0].GetFileName() << std::endl;
		// TODO: create two file for .h and .cpp
		// CppGenerator generator{ directory };
		// generator.Generate(messageSets);

		std::string filename = CodeGenUtils::RemoveSuffix(messageSets[0].GetFileName());

		std::filesystem::path header_path = directory / CodeGenUtils::AddSuffix(filename, "h");
		std::filesystem::create_directories(header_path.parent_path());
		std::filesystem::path src_path = directory / CodeGenUtils::AddSuffix(filename, "cpp");
		std::filesystem::create_directories(src_path.parent_path());
		std::ofstream headerStrm(header_path);
		std::ofstream srcStrm(src_path);

		CppGenerator generator{headerStrm, srcStrm};
		generator.Generate(messageSets);
	}



}
