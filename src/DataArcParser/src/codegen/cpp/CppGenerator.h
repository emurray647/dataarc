#include <filesystem>

#include "codegen/LanguageGenerator.h"

class CppGenerator : public LanguageGenerator {
public:

   CppGenerator(const std::filesystem::path& directory);

   void Generate(const std::vector<MessageSet>& messageSets) override;

private:

   const std::filesystem::path& _directory;
   /*std::ostream& _headerFile;
   std::ostream& _sourceFile;*/

};