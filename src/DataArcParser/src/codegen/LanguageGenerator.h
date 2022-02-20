#pragma once

#include <vector>
#include "types/MessageSet.h"

class LanguageGenerator {
public:

   enum class Language {
      CPP,
      GO,
   };

   virtual ~LanguageGenerator() {}

   virtual void Generate(const std::vector<MessageSet>& messageSets) = 0;

private:
};