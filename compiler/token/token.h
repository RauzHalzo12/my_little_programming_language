//
// Created by ortur on 19.02.2022.
//

#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_H

#include <string>
#include <memory>
#include <utility>

enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    SEPARATOR,
    OPERATOR,
    LITERAL,
};
class Token {
public:
    Token (TokenType type, const std::string& value)
            : type_(type), value_(value){}

    Token (TokenType type, std::string&& value)
        : type_(type), value_(move(value)){}

    [[nodiscard]] virtual std::string GetType() const = 0;

    [[nodiscard]] std::string GetValue() const {return value_;};

    virtual ~Token() = default;

protected:
    TokenType type_;
    const std::string value_;
};

using TokenPtr = std::unique_ptr<Token>;

TokenPtr MakeToken(TokenType type, const std::string& value);
TokenPtr MakeToken(TokenType type, std::string&& value);

std::ostream& operator<<(std::ostream& out, const TokenPtr& token);

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_H
