//
// Created by ortur on 19.02.2022.
//

#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_H

#include <string>
#include <memory>
#include <utility>

 enum class TokenType {
     IDENTIFIER = 0,
     KEYWORD = 1,
     SEPARATOR = 2,
     OPERATOR = 3,
     NUMBER = 4,
     STRING_LITERAL = 5,
     BRACKET = 6,
     UNDEFINED = 7
 };

 class IToken {
 public:
     IToken(TokenType type, const std::string& value)
             : type_(type), value_(value) {}

     IToken(TokenType type, std::string &&value)
             : type_(type), value_(move(value)) {}


     [[nodiscard]] virtual std::string GetTypeAsString() const = 0;
     [[nodiscard]] std::string_view GetValueView() const { return value_; };
     [[nodiscard]] TokenType GetType() const {return type_;}

     virtual ~IToken() = default;

 protected:
     TokenType type_;
     const std::string value_;
 };

 using TokenPtr = std::unique_ptr<IToken>;

 TokenPtr MakeToken(TokenType type, const std::string& value);
 TokenPtr MakeToken(TokenType type, std::string&& value);

 std::ostream& operator<<(std::ostream& out, const TokenPtr& token);

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_H
