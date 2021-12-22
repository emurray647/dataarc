#include "codegen/CodeGenStream.h"

CodeGenStream::CodeGenStream() : 
   //std::basic_stringstream<char>(this->std::basic_stringbuf<char>::str()),
   //CodeGenBuf(),
   std::basic_ostream<char>((CodeGenBuf*)this) {
   this->flags(std::ios_base::unitbuf);
}

void CodeGenStream::Indent() {
   _currentIndentSize += _indentSize;
}

void CodeGenStream::Unindent() {
   if (_currentIndentSize - _indentSize >= 0) {
      _currentIndentSize -= _indentSize;
   }
}

void CodeGenStream::SetIndentSize(uint32_t indentSize) {
   _indentSize = indentSize;
}

//template <>
//CodeGenStream& CodeGenStream::insert<char>(const char& c) {
//   if (c == 0) {
//      return *this;
//   }
//   if (_atStartOfLine) {
//      for (auto i = 0u; i < _currentIndentSize; ++i) {
//         *(std::basic_ostream<char>*)this << ' ';
//      }
//   }
//
//   if (c == '\n') {
//      _atStartOfLine = true;
//   }
//   else {
//      _atStartOfLine = false;
//   }
//   *(std::basic_ostream<char>*)this << in;
//   return *this;
//}

/*
std::basic_stringbuf<char>::int_type CodeGenStream::overflow(std::basic_stringbuf<char>::int_type c) {
   std::basic_stringbuf<char>::int_type ret_value = 0; // std::basic_stringbuf<char>::overflow(c);

   if (c == '\n') {
      *this << "---newline---";
   }

   std::cout << "new overflow: " << (char)c << std::endl;

   return ret_value;
}
*/