#pragma once

#include <istream>
#include <set>
#include <vector>
#include "Token.h"

class Lexer {
public:

	/// <summary>
	/// Constructs s Lexer object
	/// </summary>
	/// <param name="strm"> The stream from which to read tokens</param>
	Lexer(std::istream& strm);

	/// <summary>
	/// Creates the list of tokens read from the stream
	/// </summary>
	/// <returns>The vector of tokens read</returns>
	std::vector<Token> Tokenize();

private:

	/// <summary>
	/// Processes the stream when we don't know what type of token is being read
	/// </summary>
	void ProcessUnknown();

	/// <summary>
	/// Process the stream for when we are reading a single-character token.
	/// ie: {, }, =
	/// </summary>
	void ProcessSingleCharacterToken();

	void ProcessIdentifier();

	void ProcessLiteral();

	void ProcessStringLiteral();

	void ProcessComment();


	void FinalizeToken();


	inline char CurrentCharacter() const { 
		return _inStrm.peek(); 
	}

	inline void AdvanceStream() { 
		char c = _inStrm.get();
		++_columnNumber;
		if (c == '\n') {
			++_lineNumber;
			_columnNumber = 0;
		}
	}

	inline void ClearWhiteSpace() {
		while (isspace(CurrentCharacter())) {
			AdvanceStream();
		}
	}

	void AddToToken();

	std::vector<Token> _tokens;

	Token _currentToken;

	std::istream& _inStrm;

	static const std::set<char> SINGLE_CHAR_TOKENS;

	static const std::set<std::string> KEYWORDS;

	char _currentCharacter { 0 };

	uint32_t _lineNumber{ 0 };
	uint32_t _columnNumber{ 0 };

};