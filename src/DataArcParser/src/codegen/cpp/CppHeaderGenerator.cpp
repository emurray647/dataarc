#include "codegen/cpp/CppHeaderGenerator.h"

#include "codegen/cpp/CppCodeGenUtils.h"

CppHeaderGenerator::CppHeaderGenerator(CodeGenStream& stream) : _stream(stream) {

}

void CppHeaderGenerator::Generate(const MessageSet& messageSet) {

   GenerateIncludes(messageSet);

   GenerateOpenNamespace(messageSet);

   GenerateEnums(messageSet);

   GenerateMessages(messageSet);

   GenerateCloseNamespace(messageSet);

}

void CppHeaderGenerator::GenerateIncludes(const MessageSet& messageSet) {

   _stream << "#include <cstdint>\n";
   _stream << "#include <string>\n\n";

   for (const auto& import : messageSet.GetImports()) {
      _stream << "#include ";
      _stream << "\"" + CppCodeGenUtils::AddSuffix(CppCodeGenUtils::RemoveSuffix(import.importFileName), "h") + "\"";
      _stream << "\n";
   }

}

void CppHeaderGenerator::GenerateOpenNamespace(const MessageSet& messageSet) {
   const Package& package = messageSet.GetPackage();

   for (const std::string& name : package.packageNames) {
      _stream << "namespace " << name << " {\n";
      _stream.Indent();
   }
}

void CppHeaderGenerator::GenerateCloseNamespace(const MessageSet& messageSet) {

   const Package& package = messageSet.GetPackage();

   auto it = package.packageNames.rbegin();
   for (; it != package.packageNames.rend(); ++it) {
      _stream.Unindent();
      _stream << "} // namespace " << *it << "\n";
   }

}

void CppHeaderGenerator::GenerateEnums(const MessageSet& messageSet) {
   for (const Enum& enumclass : messageSet.GetEnums()) {
      _stream << "enum class " << enumclass.name << " {\n";
      _stream.Indent();
      for (const std::string& value : enumclass.values) {
         _stream << value << ",\n";
      }
      _stream.Unindent();
      _stream << "}; // " << enumclass.name << "\n\n";
   }
}

void CppHeaderGenerator::GenerateMessages(const MessageSet& messageSet) {
   for (const Message& message : messageSet.GetMessages()) {
      // TODO: Do we want this to inherit?
      // _stream << "class " << message.name << " : public dataarc::Message {\n";
      _stream << "class " << message.name << "{\n";
      _stream << "public:\n";
      _stream.Indent();
      _stream << "static constexpr uint32_t ID {" << message.messageID << "};\n";
      
      for (const Field& field : message.fields) {
         std::string typeString;
         if (CppCodeGenUtils::IsPrimitive(field.type)) {
            typeString = GetStringFromType(field.type);
         }
         else {
            typeString = GetStringFromType(field.type) + "&";
         }
         _stream << typeString << " get" << FirstCharToUpper(field.name) << "();\n";
         if (CppCodeGenUtils::IsPrimitive(field.type)) {
            _stream << "void set" << FirstCharToUpper(field.name) << "(" << typeString << " value" <<");\n";
         }
         else {
            _stream << "void set" << FirstCharToUpper(field.name) << "(const " << typeString << " value" <<");\n";
         }
      }


      // _stream << "bool Serialize(ByteBuffer& buffer) override;\n";
      // _stream << "bool Deserialize(ByteBuffer& buffer) override;\n";

      _stream.Unindent();

      _stream << "private:\n";
      _stream.Indent();
      for (const Field& field : message.fields) {
         std::string typeString = GetStringFromType(field.type);
         _stream << typeString << " _" << field.name << ";\n";
      }
      _stream.Unindent();

      _stream << "}; // class " << message.name << "\n\n";
   }
}

std::string CppHeaderGenerator::GetStringFromType(const DataType& datatype) {
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

