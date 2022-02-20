#pragma once

#include <cstring>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <ostream>
#include <functional>
#include <string>

typedef std::function<void(std::string)> function_type;

class CodeGenBuf : public std::streambuf {
private:
   typedef std::streambuf::traits_type traits_type;
   function_type d_function;
   char          d_buffer[1024];
   //char d_buffer[1];
   int overflow(int c) {

      std::cout << "---overflow: " << c << std::endl;

      if (!traits_type::eq_int_type(c, traits_type::eof())) {
         *this->pptr() = traits_type::to_char_type(c);
         this->pbump(1);
      }
      return this->sync() ? traits_type::not_eof(c) : traits_type::eof();
   }
   int sync() {
      if (this->pbase() != this->pptr()) {
         this->d_function(std::string(this->pbase(), this->pptr()));
         this->setp(this->pbase(), this->epptr());
      }
      return 0;
   }

public:
   CodeGenBuf(/*function_type const& function*/)
      /*: d_function(function)*/ {
      this->setp(this->d_buffer, this->d_buffer + sizeof(this->d_buffer) - 1);
      //this->setp(this->d_buffer, this->d_buffer);
      std::memset(d_buffer, 0, 1024);
   }


   char* str() const {
      return (char*)d_buffer;
   }

};


class CodeGenStream : private std::basic_stringbuf<char>, public std::basic_ostream<char> {
//class CodeGenStream : private virtual CodeGenBuf, public std::basic_ostream<char> {
public:

   CodeGenStream(); // : std::basic_stringstream<char>(this->std::basic_stringbuf<char>::str()) {}

   inline std::basic_stringbuf<char>::__string_type str() const {
      return std::basic_stringbuf<char>::str();
      //return this->CodeGenBuf::str();
   }

   //template <typename T>
   //CodeGenStream& operator <<(T& in) {
   //   //std::cout << "called" << std::endl;
   //   std::cout << "called: " << in << std::endl;
   //   return *this;
   //}

   template <typename Type>
   CodeGenStream& operator <<(Type&& in) {
      return insert(in);
   }

   void Indent();

   void Unindent();

   void SetIndentSize(uint32_t indentSize);
   
private:

   static constexpr uint32_t DEFAULT_INDENT_SIZE{ 3 };

   //std::basic_stringbuf<char>::int_type overflow(std::basic_stringbuf<char>::int_type c) override;

   uint32_t _indentSize{ DEFAULT_INDENT_SIZE };

   uint32_t _currentIndentSize{ 0 };

   bool _atStartOfLine{ true };

   //std::string

   template <typename Type>
   CodeGenStream& insert(const Type& in) {
      std::string chars = std::to_string(in);
      return insert(chars);
   }

   template <typename Type, uint32_t N>
   CodeGenStream& insert(Type(&in)[N]) {
      for (uint32_t i = 0; i < N; ++i) {
         *this << in[i];
      }
      return *this;
   }

   // template <>
   // CodeGenStream& insert<std::string>(const std::string& in) {
   CodeGenStream& insert(const std::string& in) {
      for (const char& c : in) {
         //*(std::basic_ostream<char>*)this << c;
         insert(c);
      }
      return *this;
   }


   // template <>
   // CodeGenStream& insert<char>(const char& in) {
   CodeGenStream& insert(const char& in) {
      if (in == 0) {
         return *this;
      }
      if (_atStartOfLine) {
         for (auto i = 0u; i < _currentIndentSize; ++i) {
            *(std::basic_ostream<char>*)this << ' ';
         }
      }

      if (in == '\n') {
         _atStartOfLine = true;
      }
      else {
         _atStartOfLine = false;
      }
      *(std::basic_ostream<char>*)this << in;
      return *this;
   }

   //template <>
   //CodeGenStream& insert<char>(const char& in) {
   //   if (in != 0) {
   //      *(std::basic_ostream<char>*)this << in;
   //   }
   //   return *this;
   //}

};


