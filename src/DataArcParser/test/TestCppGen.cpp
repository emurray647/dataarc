#include <vector>

#include "gtest/gtest.h"

#include "types/MessageSet.h"
#include "codegen/cpp/CppGenerator.h"

using namespace ::testing;

TEST(TestCppGen, TestImports) {
    MessageSet messageSet;
    Import import1;
    import1.importFileName = "OtherFile.idl";
    messageSet.AddImport(import1);

    std::vector<MessageSet> messageSets {messageSet};
    
    std::stringstream headerStream;
    std::stringstream srcStream;
    CppGenerator generator(headerStream, srcStream);

    generator.Generate(messageSets);

    std::string header = headerStream.str();
    EXPECT_TRUE(header.find("#include \"OtherFile.h\"") != std::string::npos);
}