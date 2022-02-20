#include "CodeGenUtils.h"

std::string CodeGenUtils::AddSuffix(const std::string& base, const std::string& suffix) {
   return base + "." + suffix;
}

std::string CodeGenUtils::RemoveSuffix(const std::string& name) {
   uint32_t suffix_index = name.find_last_of(".");
   return name.substr(0, suffix_index);
}