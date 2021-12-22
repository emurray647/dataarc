#include "Parser.h"

#include <iostream>

#include "ParseException.h"


const std::map<std::string, DataType::Type> Parser::DATA_TYPE_MAP = [] {
   std::map<std::string, DataType::Type> map;
   map.insert(std::make_pair("bool", DataType::Type::BOOL));
   map.insert(std::make_pair("int8", DataType::Type::INT8));
   map.insert(std::make_pair("int16", DataType::Type::INT16));
   map.insert(std::make_pair("int32", DataType::Type::INT32));
   map.insert(std::make_pair("int64", DataType::Type::INT64));
   map.insert(std::make_pair("uint8", DataType::Type::UINT8));
   map.insert(std::make_pair("uint16", DataType::Type::UINT16));
   map.insert(std::make_pair("uint32", DataType::Type::UINT32));
   map.insert(std::make_pair("uint64", DataType::Type::UINT64));
   map.insert(std::make_pair("float", DataType::Type::FLOAT));
   map.insert(std::make_pair("double", DataType::Type::DOUBLE));
   map.insert(std::make_pair("string", DataType::Type::STRING));
   return map;
}();

Parser::Parser(std::vector<Token> tokens) :
   _tokens(tokens)
{
   _currentToken = _tokens.begin();

}

MessageSet Parser::Parse() {
   ParseFile();
   return _messageSet;
}



void Parser::ParseFile() {
   

   while (true) {
      if (CurrentToken().type == TokenType::END_OF_FILE) {
         break;
      }

      if (CurrentToken().type != TokenType::KEYWORD) {
         // TODO: throw here
      }

      if (CurrentToken().text.compare("import") == 0) {
         ParseImport();
      }
      else if (CurrentToken().text.compare("package") == 0) {
         ParsePackage();
      }
      else if (CurrentToken().text.compare("enum") == 0) {
         ParseEnum();
      }
      else if (CurrentToken().text.compare("message") == 0) {
         ParseMessage();
      }
      else {
         // TODO:
         std::cout << "error" << std::endl;
      }
   }
}

void Parser::ParseImport() {
   Import import;
   
   AdvanceToken();

   if (CurrentToken().type == TokenType::STRING_LITERAL) {
      import.importFileName = CurrentToken().text;
   }

   AdvanceToken();

   _messageSet.AddImport(import);
}

void Parser::ParsePackage() {
   Package package;

   AdvanceToken();

   VerifyType(CurrentToken(), TokenType::IDENTIFIER);
   package.packageNames.push_back(CurrentToken().text);

   AdvanceToken();

   while (CurrentToken().type != TokenType::SEMICOLON) {
      VerifyType(CurrentToken(), TokenType::DOT_SEPARATOR);
      AdvanceToken();

      VerifyType(CurrentToken(), TokenType::IDENTIFIER);
      package.packageNames.push_back(CurrentToken().text);
      AdvanceToken();
   }

   // advance past the semicolon
   AdvanceToken();
   
   _messageSet.SetPackage(package);
}

void Parser::ParseEnum() {

   Enum enumClass;

   AdvanceToken();

   VerifyType(CurrentToken(), TokenType::IDENTIFIER);
   enumClass.name = CurrentToken().text;
   AdvanceToken();

   VerifyType(CurrentToken(), TokenType::OPEN_CURLEY_BRACE);
   AdvanceToken();

   VerifyType(CurrentToken(), TokenType::IDENTIFIER);
   enumClass.values.push_back(CurrentToken().text);
   AdvanceToken();

   while (CurrentToken().type != TokenType::CLOSE_CURLEY_BRACE) {
      VerifyType(CurrentToken(), TokenType::COMMA);
      AdvanceToken();

      VerifyType(CurrentToken(), TokenType::IDENTIFIER);
      enumClass.values.push_back(CurrentToken().text);
      AdvanceToken();
   }

   VerifyType(CurrentToken(), TokenType::CLOSE_CURLEY_BRACE);
   AdvanceToken();

   _messageSet.AddEnum(enumClass);
}

void Parser::ParseMessage() {
   Message message;

   AdvanceToken();

   VerifyType(CurrentToken(), TokenType::IDENTIFIER);
   message.name = CurrentToken().text;
   AdvanceToken();

   // at this point we either have the ID: [x], or we go straight into the { body }

   if (CurrentToken().type == TokenType::OPEN_BRACKET) {
      AdvanceToken();

      VerifyType(CurrentToken(), TokenType::LITERAL);
      message.messageID = atoi(CurrentToken().text.c_str());
      AdvanceToken();

      VerifyType(CurrentToken(), TokenType::CLOSE_BRACKET);
      AdvanceToken();
   }

   VerifyType(CurrentToken(), TokenType::OPEN_CURLEY_BRACE);
   AdvanceToken();

   while (CurrentToken().type != TokenType::CLOSE_CURLEY_BRACE) {
      Field field = ParseStatement();
      message.fields.push_back(field);
   }

   VerifyType(CurrentToken(), TokenType::CLOSE_CURLEY_BRACE);
   AdvanceToken();

   _messageSet.AddMessage(message);
}

Field Parser::ParseStatement() {
   Field field;
   
   
   DataType type = ParseType();
   field.type = type;

   VerifyType(CurrentToken(), TokenType::IDENTIFIER);
   field.name = CurrentToken().text;
   AdvanceToken();

   VerifyType(CurrentToken(), TokenType::SEMICOLON);
   AdvanceToken();

   return field;
}

DataType Parser::ParseType() {
   // a type is either sequence<type> or just a type (keyword or identifier)

   DataType type;

   const Token& token = CurrentToken();

   if (CurrentToken().type == TokenType::KEYWORD) {
      if (CurrentToken().text.compare("sequence") == 0) {
         type.isRepeated = true;
         // now parse the insides: < type >
         AdvanceToken();
         VerifyType(CurrentToken(), TokenType::OPEN_ANGLE_BRACKET);

         AdvanceToken();
      }
   }

   decltype(DATA_TYPE_MAP)::const_iterator it;
   if ((it = DATA_TYPE_MAP.find(CurrentToken().text)) != DATA_TYPE_MAP.end()) {
      type.type = it->second;
      AdvanceToken();
   }
   else {
      // must be an identifier
      VerifyType(CurrentToken(), TokenType::IDENTIFIER);
      type.typeName = CurrentToken().text;
      type.type = DataType::Type::CUSTOM;
      AdvanceToken();
   }

   if (type.isRepeated) {
      VerifyType(CurrentToken(), TokenType::CLOSE_ANGLE_BRACKET);
      AdvanceToken();
   }

   return type;
}

void Parser::VerifyType(const Token& token, TokenType type) const {
   if (token.type != type) {
      std::string message = "Unexpected token in " + token.filename + " at " +
         std::to_string(token.line_number) + ":" + std::to_string(token.column_number) + "\n";
      message += "Expected type " + std::to_string((int)type) + "; received " + token.text + 
         " of type " + std::to_string((int)token.type);
      throw ParseException(message);
   }
}