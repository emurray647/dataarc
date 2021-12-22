#pragma once

#include <string>

// types of token
// symbol: =
// keyword: message, package
// identify: x, variable,
// literal: "name", 22
// Curly brace: {}
// brackets: []
// parens: ()
// comments: //
// multiline comments /* */
// newline: \n 

enum class TokenType {
	SYMBOL,
	KEYWORD,
	IDENTIFIER,
	LITERAL,
	STRING_LITERAL,
	OPEN_CURLEY_BRACE,
	CLOSE_CURLEY_BRACE,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	OPEN_PAREN,
	CLOSE_PAREN,
	OPEN_ANGLE_BRACKET,
	CLOSE_ANGLE_BRACKET,
	COMMENT,
	MULTILINE_COMMENT,
	DOT_SEPARATOR,
	SEMICOLON,
	COMMA,
	END_OF_FILE,
	UNKNOWN
};

struct Token {
	std::string text {""};
	TokenType type {TokenType::UNKNOWN};

	uint32_t line_number;
	uint32_t column_number;
	std::string filename;
};