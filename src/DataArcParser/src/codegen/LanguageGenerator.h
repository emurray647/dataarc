#pragma once

#include <vector>
#include "types/MessageSet.h"

class LanguageGenerator {
public:

   enum class Language {
      CPP
   };

   virtual ~LanguageGenerator() {}

   virtual void Generate(const std::vector<MessageSet>& messageSets) = 0;

private:
};