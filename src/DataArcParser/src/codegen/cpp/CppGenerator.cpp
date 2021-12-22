#include "CppGenerator.h"

#include "CppHeaderGenerator.h"
#include "CppSourceGenerator.h"
#include "CppCodeGenUtils.h"

#include <fstream>

CppGenerator::CppGenerator(const std::filesystem::path& directory) :
   _directory(directory)
{

}
   

void CppGenerator::Generate(const std::vector<MessageSet>& messageSets) {

   //std::filesystem::path& path = _directory;

   for (const MessageSet& messageSet : messageSets) {

      std::string file_name_base = CppCodeGenUtils::RemoveSuffix(messageSet.GetFileName());
      std::cout << "filename: " << messageSet.GetFileName() << std::endl;
      std::cout << "base: " << file_name_base << std::endl;
      std::cout << "path: " << _directory.string() << std::endl;

      {
         CodeGenStream headerStream;
         CppHeaderGenerator headerGenerator(headerStream);
         headerGenerator.Generate(messageSet);
         std::filesystem::path header_path = _directory / (file_name_base + ".h");
         std::filesystem::create_directories(header_path.parent_path());
         std::ofstream strm(header_path);
         strm << headerStream.str();
      }

      {
         CodeGenStream sourceStream;
         CppSourceGenerator sourceGenerator(sourceStream);
         sourceGenerator.Generate(messageSet);
         std::filesystem::path source_path = _directory / (file_name_base + ".cpp");
         std::filesystem::create_directories(source_path.parent_path());
         std::ofstream strm(source_path);
         strm << sourceStream.str();
      }
   }



}