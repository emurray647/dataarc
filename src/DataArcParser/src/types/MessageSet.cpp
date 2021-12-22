#include "MessageSet.h"

void MessageSet::AddImport(Import& import) {
   _imports.push_back(import);
}

void MessageSet::SetPackage(Package& package) {
   _package = package;
}

void MessageSet::AddEnum(Enum& enumValue) {
   _enums.push_back(enumValue);
}

void MessageSet::AddMessage(Message& message) {
   _messages.push_back(message);
}