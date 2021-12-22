#pragma once

#include <vector>

#include "Package.h"
#include "Import.h"
#include "Enum.h"
#include "Message.h"

class MessageSet {

public:

   void SetFileName(const std::string& filename) {
      _filename = filename;
   }

   const std::string& GetFileName() const {
      return _filename;
   }



   void AddImport(Import& import);

   void SetPackage(Package& package);

   void AddEnum(Enum& enumValue);

   void AddMessage(Message& message);

   const std::vector<Import>& GetImports() const {
      return _imports;
   }

   const Package& GetPackage() const {
      return _package;
   }

   const std::vector<Enum>& GetEnums() const {
      return _enums;
   }

   const std::vector<Message>& GetMessages() const {
      return _messages;
   }

private:
   
   std::vector<Import> _imports;
   Package _package;
   std::vector<Enum> _enums;
   std::vector<Message> _messages;
   std::string _filename;

};