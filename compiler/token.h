//
// Created by ortur on 01.04.2022.
//

#ifndef DSL_TOKEN_H
#define DSL_TOKEN_H

#include <unordered_map>
#include <vector>
#include <string_view>
#include <regex>
#include <boost/regex.hpp>

struct Token {

    // ТЕРМИНАЛЫ
    enum class Type {
        FOR_KEYWORD,
        WHILE_KEYWORD,
        STRUCT_KEYWORD,
        IF_KEYWORD,
        ELSE_KEYWORD,
        LOAD_KEYWORD,
        OPERATOR,
        ASSIGN_OPERATOR,

        CURLY_OPEN_BRACE,
        CURLY_CLOSE_BRACE,
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,

        NUMBER_CONSTANT,
        STRING_CONSTANT,
        IDENTIFIER,

        ENDLINE,
        SPACE,
        TAB,

        COMMA,
        SEMICOLON,
        UNDEFINED
    };

    Token(Type type, std::string_view value = "")
        : type(type), value(std::string(value)){};

    const Type type;
    const std::string value;
};

static const boost::regex IDENTIFIER_REGEX      ( R"([_]*[a-zA-Z][a-zA-Z0-9_]*)");
static const boost::regex STRING_CONSTANT_REGEX ( R"("(\\.|[^\\"])*")");
static const boost::regex NUMBER_CONSTANT_REGEX ( R"([+-]?\d+)");

static const std::unordered_map<std::string_view, Token::Type> KEYWORDS = {
        {"for", Token::Type::FOR_KEYWORD},
        {"while", Token::Type::WHILE_KEYWORD},
        {"if", Token::Type::IF_KEYWORD},
        {"else", Token::Type::ELSE_KEYWORD},
        {"load", Token::Type::LOAD_KEYWORD},
        {"struct", Token::Type::STRUCT_KEYWORD},
};

static const std::unordered_map<std::string_view, Token::Type> OPERATORS = {
        {"+", Token::Type::OPERATOR},
        {"-", Token::Type::OPERATOR},
        {"*", Token::Type::OPERATOR},
        {"/", Token::Type::OPERATOR},
        {"%", Token::Type::OPERATOR},
        {".", Token::Type::OPERATOR},
};

static const std::unordered_map<std::string_view, Token::Type> ASSIGN_OPERATOR = {
        {"=",  Token::Type::ASSIGN_OPERATOR},
        {"+=", Token::Type::ASSIGN_OPERATOR},
        {"-=", Token::Type::ASSIGN_OPERATOR},
        {"*=", Token::Type::ASSIGN_OPERATOR},
        {"/=", Token::Type::ASSIGN_OPERATOR},
        {"%=", Token::Type::ASSIGN_OPERATOR},
};

static const std::unordered_map<std::string_view, Token::Type> BRACES = {
        {"(",  Token::Type::OPEN_PARENTHESIS},
        {")",  Token::Type::CLOSE_PARENTHESIS},
        {"{",  Token::Type::CURLY_OPEN_BRACE},
        {"}",  Token::Type::CURLY_CLOSE_BRACE},
};

static const std::unordered_map<std::string_view, Token::Type> SEPARATORS = {
        {" ",  Token::Type::SPACE},
        //{R"(\\s)",  Token::Type::SPACE},
        {"\t",  Token::Type::TAB},
        {"\n",  Token::Type::ENDLINE},
        {";",  Token::Type::SEMICOLON},
        {",",  Token::Type::COMMA},
};

static const  std::unordered_map<Token::Type, std::string> TYPE_TO_STR = {
        {Token::Type::FOR_KEYWORD, "for_kv"},
        {Token::Type::IF_KEYWORD, "if_kv"},
        {Token::Type::WHILE_KEYWORD, "while_kv"},
        {Token::Type::ELSE_KEYWORD, "else_kv"},
        {Token::Type::LOAD_KEYWORD, "load_kv"},
        {Token::Type::STRUCT_KEYWORD, "struct_kv"},

};

bool IsKeyword(const std::string_view& lexem);
bool IsOperator(const std::string_view& lexem);
bool IsAssignOperator(const std::string_view& lexem);
bool IsBrace(const std::string_view& lexem);
bool IsSeparator(const std::string_view& lexem);
bool IsIdentifier(const std::string_view& lexem);
bool IsStringConstant(const std::string_view& lexem);


bool IsNumberConstant(const std::string_view& lexem);


std::optional<Token::Type> GetTokenType(std::string_view lexem);
std::optional<Token> GetNextToken(std::string_view& text);

std::vector<Token> SplitIntoTokens(std::string_view text);

std::ostream& operator << (std::ostream& out, const Token& t);

#endif //DSL_TOKEN_H
