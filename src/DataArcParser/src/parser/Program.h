#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <istream>

#include "Lexer.h"
#include "Parser.h"

class Program {
public:
    Program(std::istream& strm);

    MessageSet Parse();

private:

    Lexer _lexer;

    // Parser _parser;


};

#endif // PROGRAM_H_