
#include "CppCodeGenUtils.h"

std::string CppCodeGenUtils::GetStringFromType(const DataType& datatype) {
   std::string return_value;

   switch (datatype.type) {
   case DataType::Type::BOOL:
      return_value = "bool";
      break;
   case DataType::Type::UINT8:
      return_value = "uint8_t";
      break;
   case DataType::Type::UINT16:
      return_value = "uint16_t";
      break;
   case DataType::Type::UINT32:
      return_value = "uint32_t";
      break;
   case DataType::Type::UINT64:
      return_value = "uint64_t";
      break;
   case DataType::Type::INT8:
      return_value = "int8_t";
      break;
   case DataType::Type::INT16:
      return_value = "int16_t";
      break;
   case DataType::Type::INT32:
      return_value = "int32_t";
      break;
   case DataType::Type::INT64:
      return_value = "int64_t";
      break;
   case DataType::Type::FLOAT:
      return_value = "float";
      break;
   case DataType::Type::DOUBLE:
      return_value = "double";
      break;
   case DataType::Type::STRING:
      return_value = "std::string";
      break;
   case DataType::Type::CUSTOM:
      return_value = datatype.typeName;
      break;
   }

   return return_value;

}

bool CppCodeGenUtils::IsPrimitive(const DataType& datatype) {
   return !datatype.isRepeated && datatype.type != DataType::Type::STRING && datatype.type != DataType::Type::CUSTOM;
}

std::string CppCodeGenUtils::AddSuffix(const std::string& base, const std::string& suffix) {
   return base + "." + suffix;
}

std::string CppCodeGenUtils::RemoveSuffix(const std::string& name) {
   uint32_t suffix_index = name.find_last_of(".");
   return name.substr(0, suffix_index);
}