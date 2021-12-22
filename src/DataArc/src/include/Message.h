#pragma once

#include "ByteBuffer.h"

namespace dataarc {

   class Message {
   public:

      virtual ~Message() {}

      bool Serialize(ByteBuffer& buffer) = 0

      bool Deserialize(const ByteBuffer& buffer) = 0;

   private:
   };


}