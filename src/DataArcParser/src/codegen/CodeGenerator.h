#pragma once

#include <vector>
#include "LanguageGenerator.h"

class CodeGenerator {
public:
   using Language = LanguageGenerator::Language;

   //void Initialize();

   void AddLanguage(Language language);

private:
};