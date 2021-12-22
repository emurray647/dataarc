#pragma once

#include <cstdint>

struct ByteBufferDefaultAllocator;
struct ByteBufferDefaultDeallocator;

namespace dataarc {

using Byte = uint8_t;

template <typename Deleter=ByteBufferDefaultDeallocator, typename Allocator=ByteBufferDefaultAllocator>
class ByteBuffer {

   //using Byte = uint8_t;

   ByteBuffer();

   ~ByteBuffer();

   void allocate(uint32_t bytes);

   void deallocate(uint32_t bytes);

   Byte* data();

   uint32_t size() const;

   uint32_t allocatedBytes() const;

   bool write(Byte* bytes, uint32_t size);

   bool write(Byte* bytes, uint32_t size, uint32_t location);

   void setLocation(uint32_t location);

private:
   Byte* _data{ nullptr };
   uint32_t _size;
   uint32_t _allocatedBytes;

   uint32_t _currentLocation{0};


};

struct ByteBufferDefaultAllocator {
   Byte* allocate(uint32_t size);
};

struct ByteBufferDefaultDeallocator {
   void deallocate(Byte*& buffer);
};

template <typename Deleter, typename Allocator>
ByteBuffer<Deleter, Allocator>::~ByteBuffer() {
   deallocate(_allocatedBytes);
}

template <typename Deleter, typename Allocator>
void ByteBuffer<Deleter, Allocator>::allocate(uint32_t bytes) {
   _data = Allocator::allocate(bytes);
   _size = 0;
   _allocatedBytes = bytes;
   setLocation(0);

}

template <typename Deleter, typename Allocator>
void ByteBuffer<Deleter, Allocator>::deallocate(uint32_t bytes) {
   Deleter::deallocate(_data);
   _size = 0;
   _allocatedBytes = 0;
}

template <typename Deleter, typename Allocator>
Byte* ByteBuffer<Deleter, Allocator>::data() {
   return _data;
}

template <typename Deleter, typename Allocator>
uint32_t ByteBuffer<Deleter, Allocator>::size() const {
   return _size;
}

template <typename Deleter, typename Allocator>
uint32_t ByteBuffer<Deleter, Allocator>::allocatedBytes() const {
   return _allocatedBytes;
}

template <typename Deleter, typename Allocator>
bool ByteBuffer<Deleter, Allocator>::write(Byte* bytes, uint32_t size) {
   if (write(bytes, size, _currentLocation)) {
      _currentLocation += size;
      return true;
   }
   return false;
}

template <typename Deleter, typename Allocator>
bool ByteBuffer<Deleter, Allocator>::write(Byte* bytes, uint32_t size, uint32_t location) {
   // if we don't have enough room, return false
   if ((_allocatedBytes - _size) < size) {
      return false;
   }

   // write into the buffer
   memcpy(_data + location, bytes, size);

   // make sure the _size is correct
   if (location + size > _size) {
      _size = location + size;
   }
}

template <typename Deleter, typename Allocator>
void ByteBuffer<Deleter, Allocator>::setLocation(uint32_t location) {
   _currentLocation = 0;
}

}