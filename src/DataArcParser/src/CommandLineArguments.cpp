#include "CommandLineArguments.h"

const char* CommandLineArguments::INPUT_DIRECTORY_ARG = "--input";
const char* CommandLineArguments::OUTPUT_CPP_DIRECTORY_ARG = "--output-cpp";

void CommandLineArguments::Parse(int argc, char** argv) {

   for (int i = 1; i < argc; ++i) {
      if (strcmp(argv[i], INPUT_DIRECTORY_ARG) == 0) {
         _inputDirectories.push_back(std::string(argv[i + 1]));
      }
      else if (strcmp(argv[i], OUTPUT_CPP_DIRECTORY_ARG) == 0) {
         _outputCppDirectory = std::string(argv[i + 1]);
      }
   }

}

const std::vector<std::string>& CommandLineArguments::GetInputDirectories() const {
   return _inputDirectories;
}

const std::string& CommandLineArguments::GetOutputCppDirectory() const {
   return _outputCppDirectory;
}