#include "CppSourceGenerator.h"
#include "codegen/cpp/CppCodeGenUtils.h"

CppSourceGenerator::CppSourceGenerator(CodeGenStream& stream) :
   _stream(stream) {

}

void CppSourceGenerator::Generate(const MessageSet& messageSet) {

   _stream << "#include \"" << CppCodeGenUtils::RemoveSuffix(messageSet.GetFileName()) << ".h" << "\"\n";

   const Package& package = messageSet.GetPackage();

   for (const std::string& name : package.packageNames) {
      _stream << "namespace " << name << " {\n";
      _stream.Indent();
   }

   GenerateMethods(messageSet.GetMessages());

   // GenerateSerializationMethods(messageSet.GetMessages());

   auto it = package.packageNames.rbegin();
   for (; it != package.packageNames.rend(); ++it) {
      _stream.Unindent();
      _stream << "} // namespace " << *it << "\n";
   }

}

void CppSourceGenerator::GenerateMethods(const std::vector<Message>& messages) {

   for (const Message& message : messages) {
      message.name;

      for (const Field& field : message.fields) {

         std::string typeString;
         if (CppCodeGenUtils::IsPrimitive(field.type)) {
            typeString = CppCodeGenUtils::GetStringFromType(field.type);
         }
         else {
            typeString = CppCodeGenUtils::GetStringFromType(field.type) + "&";
         }
         
         _stream << typeString << " " << message.name << "::get" << CppCodeGenUtils::FirstCharToUpper(field.name) << "() {\n";
         _stream.Indent();
         _stream << "return _" << field.name << ";\n";
         _stream.Unindent();
         _stream << "}\n";

         if (CppCodeGenUtils::IsPrimitive(field.type)) {
            _stream << "void " << message.name << "::set" << CppCodeGenUtils::FirstCharToUpper(field.name) << "(" << typeString << " value" << ") {\n";
         }
         else {
            _stream << "void " << message.name << "::set" << CppCodeGenUtils::FirstCharToUpper(field.name) << "(const " << typeString << " value" << ") {\n";
         }
         _stream.Indent();
         _stream << "_" << field.name << " = value;\n";
         _stream.Unindent();
         _stream << "}\n";

         _stream << "\n";

      }
   }

}

void CppSourceGenerator::GenerateSerializationMethods(const std::vector<Message>& messages) {
   for (const Message& message : messages) {

      _stream << "bool " << message.name << "::Serialize(ByteBuffer& buffer) {\n";
      _stream.Indent();

      for (const Field& field : message.fields) {
         _stream << "serialize(" << field.name << ");\n";
      }

      _stream.Unindent();
      _stream << "}\n";



      _stream << "bool " << message.name << "::Deserialize(ByteBuffer& buffer) {\n";
      _stream.Indent();

      _stream.Unindent();
      _stream << "}\n";
   }
}