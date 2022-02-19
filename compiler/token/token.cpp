//
// Created by ortur on 19.02.2022.
//
#include <iostream>
#include <string>
#include "token.h"

using namespace std;

class IdToken : public Token {
public:
    explicit IdToken(const string& value)
        : Token(TokenType::IDENTIFIER, value){}

    explicit IdToken(string&& value)
            : Token(TokenType::IDENTIFIER, move(value)){}

    [[nodiscard]] string GetType() const override {
        return "identifier";
    }
};

class KeyToken : public Token {
public:
    explicit KeyToken(const string& value)
            : Token(TokenType::KEYWORD, value){}

    explicit KeyToken(string&& value)
    : Token(TokenType::KEYWORD, move(value)){}

    [[nodiscard]] string GetType() const override {
        return "keyword";
    }
};

class SepToken : public Token {
public:
    explicit SepToken(const string& value)
            : Token(TokenType::SEPARATOR, value){}

    explicit SepToken(string&& value)
    : Token(TokenType::SEPARATOR, move(value)){}

    [[nodiscard]] string GetType() const override {
        return "separator";
    }
};

class OpToken : public Token {
public:
    explicit OpToken(const string& value)
            : Token(TokenType::OPERATOR, value){}

    explicit OpToken(string&& value)
    : Token(TokenType::OPERATOR, move(value)){}

    [[nodiscard]] string GetType() const override {
        return "operator";
    }
};

class LitToken : public Token {
public:
    explicit LitToken(const string& value)
            : Token(TokenType::LITERAL, value){}

    explicit LitToken(string&& value)
    : Token(TokenType::LITERAL, move(value)){}

    [[nodiscard]] string GetType() const override {
        return "literal";
    }
};

TokenPtr MakeToken(TokenType type, const std::string& value) {
    if (type == TokenType::IDENTIFIER) {
        return make_unique<IdToken>(value);
    } else if (type == TokenType::KEYWORD) {
        return make_unique<KeyToken>(value);
    } else if (type == TokenType::SEPARATOR) {
        return make_unique<SepToken>(value);
    } else if (type == TokenType::OPERATOR) {
        return make_unique<OpToken>(value);
    } else if (type == TokenType::LITERAL) {
        return make_unique<LitToken>(value);
    }
    return nullptr;
}

TokenPtr MakeToken(TokenType type, std::string&& value) {
    if (type == TokenType::IDENTIFIER) {
        return make_unique<IdToken>(move(value));
    } else if (type == TokenType::KEYWORD) {
        return make_unique<KeyToken>(move(value));
    } else if (type == TokenType::SEPARATOR) {
        return make_unique<SepToken>(move(value));
    } else if (type == TokenType::OPERATOR) {
        return make_unique<OpToken>(move(value));
    } else if (type == TokenType::LITERAL) {
        return make_unique<LitToken>(move(value));
    }
    return nullptr;
}

ostream& operator<<(ostream& out, const TokenPtr& token) {
    out << "[" << token->GetType() << ", " << token->GetValue() << "]";
    return out;
}
