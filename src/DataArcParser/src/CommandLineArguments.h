#pragma once

#include <string>
#include <vector>

class CommandLineArguments {
public:
   //CommandLineArguments(int argc, char** argv);

   void Parse(int argc, char** argv);

   const std::vector<std::string>& GetInputDirectories() const;

   const std::string& GetOutputCppDirectory() const;

private:

   static const char* INPUT_DIRECTORY_ARG;
   static const char* OUTPUT_CPP_DIRECTORY_ARG;

   std::vector<std::string> _inputDirectories;
   std::string _outputCppDirectory;

};