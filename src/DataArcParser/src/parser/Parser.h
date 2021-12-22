#pragma once

#include <map>
#include <vector>
#include "Token.h"
#include "parser/ParseException.h"
#include "types/MessageSet.h"

/*
Either import, package, enum, or message

File -> [IMPORT|PACKAGE|ENUM|MESSAGE]*

IMPORT -> import STRING_LITERAL
PACKAGE -> package IDENTIFIER [.IDENTIFIER]* ;
ENUM -> enum   IDENTIFIER OPEN_CURLY_BRACE [COMMA IDENTIFIER]* CLOSE_CURLY_BRACE 

MESSAGE -> message IDENTIFIER [OPEN_BRACKET LITERAL CLOSE_BRACKET]+ OPEN_CURLEY_BRACE  STATEMENT* CLOSE_CURLY_BRACE 

STATEMENT -> TYPE IDENTIFIER SEMICOLON

TYPE -> sequence < TYPE >
	  | KEYWORD|IDENTIFIER
*/


class Parser {
public:

	Parser(std::vector<Token> tokens);

	MessageSet Parse();

private:

	void ParseFile();

	void ParseImport();

	void ParsePackage();

	void ParseEnum();

	void ParseMessage();

	Field ParseStatement();

	DataType ParseType();

	void VerifyType(const Token& token, TokenType type) const;

	std::vector<Token> _tokens;

	std::vector<Token>::const_iterator _currentToken;

	MessageSet _messageSet;

	inline const Token& CurrentToken() { 
		if (_currentToken != _tokens.end()) {
			return *_currentToken;
		}
		// TODO
		throw ParseException("Prematurely reached end of token list");
	}
	inline void AdvanceToken() { 
		_currentToken = std::next(_currentToken); 
	}

	static const std::map<std::string, DataType::Type> DATA_TYPE_MAP;

};