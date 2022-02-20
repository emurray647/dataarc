#pragma once

#include "codegen/CodeGenStream.h"
#include "types/MessageSet.h"

class CppHeaderGenerator {
public:

   CppHeaderGenerator(CodeGenStream& stream); // : _stream(stream) {}

   void Generate(const MessageSet& messageSet);

private:

   void GenerateIncludes(const MessageSet& messageSet);

   void GenerateOpenNamespace(const MessageSet& messageSet);

   void GenerateCloseNamespace(const MessageSet& messageSet);

   void GenerateEnums(const MessageSet& messageSet);
   
   void GenerateMessages(const MessageSet& messageSet);

   static std::string FirstCharToUpper(const std::string& string) {
      std::string returnString(string);
      returnString[0] = std::toupper(string[0]);
      return returnString;
   }

   static std::string GetStringFromType(const DataType& datatype);

   static bool IsPrimitive(const DataType& datatype);

   CodeGenStream& _stream;

};