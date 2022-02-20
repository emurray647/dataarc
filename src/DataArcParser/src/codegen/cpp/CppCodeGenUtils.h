#pragma once

#include <string>

#include "types/DataType.h"

class CppCodeGenUtils {
public:

   static std::string FirstCharToUpper(const std::string& string) {
      std::string returnString(string);
      returnString[0] = std::toupper(string[0]);
      return returnString;
   }

   static std::string GetStringFromType(const DataType& datatype);

   static bool IsPrimitive(const DataType& datatype);

   static std::string AddSuffix(const std::string& base, const std::string& suffix);

   static std::string RemoveSuffix(const std::string & name);

   void GenerateMethodSignature(const std::string& type,
      int n);


};
