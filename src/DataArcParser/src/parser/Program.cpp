#include "Program.h"

Program::Program(std::istream& strm) :
    _lexer(strm) {

}

MessageSet Program::Parse() {
    std::vector<Token> tokens = _lexer.Tokenize();

    Parser parser(tokens);
    return parser.Parse();
}