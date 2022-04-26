//
// Created by ortur on 01.04.2022.
//

#ifndef DSL_TOKEN_H
#define DSL_TOKEN_H

#include <unordered_map>
#include <vector>
#include <string_view>
#include <regex>

#include <boost/regex/icu.hpp>
#include <boost/regex.hpp>


struct Token {

    // ТЕРМИНАЛЫ
    enum class Type {
        //KEYWORDS
        //FOR_KEYWORD,
        //WHILE_KEYWORD,
        //STRUCT_KEYWORD,
        //IF_KEYWORD,
        //ELSE_KEYWORD,
        //LOAD_KEYWORD,
        //RETURN_KEYWORD,
        //DO_KEYWORD,
        //FUNC_KEYWORD,
        //FIELD_KEYWORD,
        VAR_KEYWORD,



        ADD_OPERATOR,
        SUB_OPERATOR,
        MUL_OPERATOR,
        DIV_OPERATOR,
        MOD_OPERATOR,
        DOT_OPERATOR,

        ASSIGN_OPERATOR,

        /*CURLY_OPEN_BRACE,
        CURLY_CLOSE_BRACE,
         */
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        //OPEN_SQUARE_BRACE,
        //CLOSE_SQUARE_BRACE,

        NUMBER_CONSTANT,
        STRING_CONSTANT,
        IDENTIFIER,

        ENDLINE,
        SPACE,
        TAB,

        COMMA,
        SEMICOLON,
        UNDEFINED,

        /*
        STRUCT_NAME,
        FUNC_NAME,
        FIELD_NAME,
        */

        VAR_NAME,

        BASIC_INT,
        BASIC_STRING,

    };

    explicit Token(Type type, std::string_view value = "")
        : type(type), value(std::string(value)){};


    const std::string value;
    Type type;
    int line_number;
};



const std::regex IDENTIFIER_REGEX       ( R"([a-zA-Z_]+)");
const std::regex STRING_CONSTANT_REGEX  ( R"("(\\.|[^\\"])*")" );
//const std::regex STRING_CONSTANT_REGEX  ( R"("(?:\\\\.|\\\\\\n|[^\"\\\\\\n])*")" );
const std::regex NUMBER_CONSTANT_REGEX  ( R"([-]?\d+)"        );


const std::unordered_map<std::string_view, Token::Type> KEYWORDS = {
        //{"for",         Token::Type::FOR_KEYWORD},
        //{"while",       Token::Type::WHILE_KEYWORD},
        //{"if",          Token::Type::IF_KEYWORD},
        //{"else",        Token::Type::ELSE_KEYWORD},
        //{"load",        Token::Type::LOAD_KEYWORD},
        //{"return",      Token::Type::RETURN_KEYWORD},
        //{"do",          Token::Type::DO_KEYWORD},
        //{"struct",      Token::Type::STRUCT_KEYWORD},
        //{"func",        Token::Type::FUNC_KEYWORD},
        //{"field",       Token::Type::FIELD_KEYWORD},
        {"var",         Token::Type::VAR_KEYWORD},
};

const std::unordered_map<std::string_view, Token::Type> OPERATORS = {
        {"+", Token::Type::ADD_OPERATOR},
        {"-", Token::Type::SUB_OPERATOR},
        {"*", Token::Type::MUL_OPERATOR},
        {"/", Token::Type::DIV_OPERATOR},
        {"%", Token::Type::MOD_OPERATOR},
        {".", Token::Type::DOT_OPERATOR},
};

const std::unordered_map<std::string_view, Token::Type> BASIC_DATA_TYPES = {
        {"Int", Token::Type::BASIC_INT},
        {"String", Token::Type::BASIC_STRING},
};

const std::unordered_map<std::string_view, Token::Type> ASSIGN_OPERATOR = {
        {"=",  Token::Type::ASSIGN_OPERATOR},
       //{"+=", Token::Type::ASSIGN_OPERATOR},
       //{"-=", Token::Type::ASSIGN_OPERATOR},
       //{"*=", Token::Type::ASSIGN_OPERATOR},
       //{"/=", Token::Type::ASSIGN_OPERATOR},
       //{"%=", Token::Type::ASSIGN_OPERATOR},
};

const std::unordered_map<std::string_view, Token::Type> BRACES = {
        {"(",  Token::Type::OPEN_PARENTHESIS},
        {")",  Token::Type::CLOSE_PARENTHESIS},
        //{"{",  Token::Type::CURLY_OPEN_BRACE},
        //{"}",  Token::Type::CURLY_CLOSE_BRACE},
        //{"[",  Token::Type::OPEN_SQUARE_BRACE},
        //{"]",  Token::Type::CLOSE_SQUARE_BRACE},
};

const std::unordered_map<std::string_view, Token::Type> SEPARATORS = {
        {" ",  Token::Type::SPACE},
        {"\t", Token::Type::TAB},
        {"\n", Token::Type::ENDLINE},
        {";",  Token::Type::SEMICOLON},
        {",",  Token::Type::COMMA},
};


bool IsKeyword(const std::string_view& lexem);
bool IsOperator(const std::string_view& lexem);
bool IsAssignOperator(const std::string_view& lexem);
bool IsBrace(const std::string_view& lexem);
bool IsSeparator(const std::string_view& lexem);
bool IsIdentifier(const std::string_view& lexem);
bool IsStringConstant(const std::string_view& lexem);
bool IsNumberConstant(const std::string_view& lexem);
bool IsBasicDataType(const std::string_view& lexem);

std::optional<Token::Type> GetTokenType(std::string_view lexem);
std::optional<Token> GetNextToken(std::string_view& text);


class TokenStream {
public:


    explicit TokenStream(const std::vector<Token>& token_sequence);
    explicit TokenStream(std::vector<Token>&& token_sequence);

    TokenStream(TokenStream&&) = default;
    TokenStream(const TokenStream&) = delete;
    TokenStream& operator=(const TokenStream&) = delete;


    Token& GetCurrentToken();
    const Token& GetCurrentToken() const;

    bool HasNext() const;
    bool HasCurrent() const;


    const Token& GetNextToken() const;
    Token& GetNextToken();

    void MoveToNextToken();
    void MoveToPrevToken();

    const auto begin() const {
        return tokens_.begin();
    }

    const auto end() const {
        return tokens_.end();
    }
private:
    std::vector<Token> tokens_;
    size_t curr_idx = 0;
};

std::vector<Token> SplitIntoTokens(std::string_view text);



#endif //DSL_TOKEN_H
