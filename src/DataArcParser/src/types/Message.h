#pragma once

#include "Field.h"

struct Message {
   std::string name;

   uint32_t messageID;
   
   std::vector<Field> fields;
};