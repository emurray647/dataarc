#pragma once

#include "codegen/CodeGenStream.h"
#include "types/MessageSet.h"

class CppSourceGenerator {
public:

   CppSourceGenerator(CodeGenStream& stream);

   void Generate(const MessageSet& messageSet);

private:

   void GenerateMethods(const std::vector<Message>& messages);

   void GenerateSerializationMethods(const std::vector<Message>& messages);

   CodeGenStream& _stream;
};