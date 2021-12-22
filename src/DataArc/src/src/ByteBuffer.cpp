#include "ByteBuffer.h"

namespace dataarc {

   Byte* ByteBufferDefaultAllocator::allocate(uint32_t size) {
      return new Byte[size];
   }

   void ByteBufferDefaultDeallocator::deallocate(Byte*& data) {
      if (data != nullptr) {
         delete[] data;
         data = nullptr;
      }
   }

}