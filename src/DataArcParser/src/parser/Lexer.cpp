#include "Lexer.h"
#include <cstdio>
#include <ctype.h>
#include <iostream>

const std::set<char> Lexer::SINGLE_CHAR_TOKENS =
	{ '(', ')', '{', '}', '[', ']', '<', '>', '=', ';', '.', ',' };

const std::set<std::string> Lexer::KEYWORDS = {
	"import", "package", "enum", "message",
	"string", "bool", "repeated",
	"int8", "int16", "int32", "int64",
	"uint8", "uint16", "uint32", "uint64",
	"float", "double"
};

bool is_identifier_char(char c) {
	return isalnum(c) || c == '_';
}


Lexer::Lexer(std::istream& istrm) :
	_inStrm(istrm) {
	
	_currentToken.type = TokenType::UNKNOWN;
}

std::vector<Token> Lexer::Tokenize() {

	ProcessUnknown();

	// do a final pass through the tokens, and set any keywords to the keyword token
	for (auto& token : _tokens) {
		if (token.type == TokenType::IDENTIFIER && KEYWORDS.find(token.text) != KEYWORDS.end()) {
			token.type = TokenType::KEYWORD;
		}
	}

	return _tokens;


}

void Lexer::FinalizeToken()
{
	_tokens.push_back(_currentToken);
	_currentToken.text.clear();
	_currentToken.type = TokenType::UNKNOWN;
}

void Lexer::ProcessUnknown() {

	// remove leading whitespace
	//_inStrm >> std::ws;
	ClearWhiteSpace();

	char c = CurrentCharacter();

	// at this point, we are past whitespace, so we know that the token starts here
	_currentToken.column_number = _columnNumber;
	_currentToken.line_number = _lineNumber;

	if (c == EOF) {
		_currentToken.type = TokenType::END_OF_FILE;
		FinalizeToken();
		return;
	}

	if (SINGLE_CHAR_TOKENS.find(c) != SINGLE_CHAR_TOKENS.end()) {
		ProcessSingleCharacterToken();
	}
	else if (isdigit(c)) {
		ProcessLiteral();
	}
	else if (isalpha(c)) {
		ProcessIdentifier();
	}
	else if (c == '"') {
		ProcessStringLiteral();
	}
	else if (c == '/') {
		ProcessComment();
	}
	else {
		AddToToken();

		ProcessUnknown();
	}

}

void Lexer::ProcessSingleCharacterToken() {
	//{ '(', ')', '{', '}', '[', ']', '=', ';', '.', ',' };
	
	if (CurrentCharacter() == '(') {
		_currentToken.type = TokenType::OPEN_PAREN;
	}
	else if (CurrentCharacter() == ')') {
		_currentToken.type = TokenType::CLOSE_PAREN;
	}
	else if (CurrentCharacter() == '{') {
		_currentToken.type = TokenType::OPEN_CURLEY_BRACE;
	}
	else if (CurrentCharacter() == '}') {
		_currentToken.type = TokenType::CLOSE_CURLEY_BRACE;
	}
	else if (CurrentCharacter() == '[') {
		_currentToken.type = TokenType::OPEN_BRACKET;
	}
	else if (CurrentCharacter() == ']') {
		_currentToken.type = TokenType::CLOSE_BRACKET;
	}
	else if (CurrentCharacter() == '<') {
		_currentToken.type = TokenType::OPEN_ANGLE_BRACKET;
	}
	else if (CurrentCharacter() == '>') {
		_currentToken.type = TokenType::CLOSE_ANGLE_BRACKET;
	}
	else if (CurrentCharacter() == '=') {
		_currentToken.type = TokenType::SYMBOL;
	}
	else if (CurrentCharacter() == ';') {
		_currentToken.type = TokenType::SEMICOLON;
	}
	else if (CurrentCharacter() == '.') {
		_currentToken.type = TokenType::DOT_SEPARATOR;
	}
	else if (CurrentCharacter() == ',') {
		_currentToken.type = TokenType::COMMA;
	}

	AddToToken();
	FinalizeToken();
	ProcessUnknown();


}

void Lexer::ProcessIdentifier() {
	_currentToken.type = TokenType::IDENTIFIER;

	char c = CurrentCharacter();

	if (is_identifier_char(c)) {
		AddToToken();
		ProcessIdentifier();
	}
	else {
		// the identifier is done
		FinalizeToken();
		ProcessUnknown();
	}
	
}

void Lexer::ProcessLiteral() {
	_currentToken.type = TokenType::LITERAL;
	char c = CurrentCharacter();

	if (isdigit(c)) {
		AddToToken();
		ProcessLiteral();
	}
	else {
		FinalizeToken();
		ProcessUnknown();
	}
}

void Lexer::ProcessStringLiteral() {
	_currentToken.type = TokenType::STRING_LITERAL;
	char c = CurrentCharacter();
	AddToToken();

	while (CurrentCharacter() != '"') {
		AddToToken();
	}
	// c is "
	AddToToken();

	FinalizeToken();
	ProcessUnknown();

}

void Lexer::ProcessComment() {
	AddToToken();

	if (CurrentCharacter() == '/') {
		// single line comment
		while (CurrentCharacter() != '\n') {
			AddToToken();
		}
		AddToToken();
		_currentToken.type = TokenType::UNKNOWN;
		_currentToken.text = "";
	}
	else if (CurrentCharacter() == '*') {
		// multi-line comment
		// TODO
	}
	else {
		std::cout << "Error" << std::endl;
	}

	ProcessUnknown();

}

void Lexer::AddToToken() {
	_currentToken.text += CurrentCharacter();
	AdvanceStream();
}