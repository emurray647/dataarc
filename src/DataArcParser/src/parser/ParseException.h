#pragma once

#include <stdexcept>

class ParseException : public std::runtime_error {

public:

   ParseException(const std::string& msg) :
      runtime_error(msg) {}

};