//
// Created by ortur on 19.02.2022.
//
#include <iostream>
#include <string>
#include "token.h"

using namespace std;

class IdToken : public IToken {
public:
    explicit IdToken(const string& value)
        : IToken(TokenType::IDENTIFIER, value){}

    explicit IdToken(string&& value)
            : IToken(TokenType::IDENTIFIER, move(value)){}

    [[nodiscard]] string GetTypeAsString() const override {
        return "identifier";
    }

};

class KeyToken : public IToken {
public:
    explicit KeyToken(const string& value)
            : IToken(TokenType::KEYWORD, value){}

    explicit KeyToken(string&& value)
    : IToken(TokenType::KEYWORD, move(value)){}

    [[nodiscard]] string GetTypeAsString() const override {
        return "keyword";
    }
};

class SepToken : public IToken {
public:
    explicit SepToken(const string& value)
            : IToken(TokenType::SEPARATOR, value){}

    explicit SepToken(string&& value)
    : IToken(TokenType::SEPARATOR, move(value)){}

    [[nodiscard]] string GetTypeAsString() const override {
        return "separator";
    }
};

class OpToken : public IToken {
public:
    explicit OpToken(const string& value)
            : IToken(TokenType::OPERATOR, value){}

    explicit OpToken(string&& value)
    : IToken(TokenType::OPERATOR, move(value)){}

    [[nodiscard]] string GetTypeAsString() const override {
        return "operator";
    }
};

class LitToken : public IToken {
public:
    explicit LitToken(const string& value)
            : IToken(TokenType::LITERAL, value){}

    explicit LitToken(string&& value)
    : IToken(TokenType::LITERAL, move(value)){}

    [[nodiscard]] string GetTypeAsString() const override {
        return "literal";
    }
};


class UndefToken : public IToken {
public:
    explicit UndefToken(const string& value)
            : IToken(TokenType::UNDEFINED, value){}

    explicit UndefToken(string&& value)
            : IToken(TokenType::UNDEFINED, move(value)){}

    [[nodiscard]] string GetTypeAsString() const override {
        return "undefined";
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
    } else if (type == TokenType::UNDEFINED) {
        return make_unique<UndefToken>(value);
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
    } else if (type == TokenType::UNDEFINED) {
        return make_unique<UndefToken>(move(value));
    }
    return nullptr;
}

ostream& operator<<(ostream& out, const TokenPtr& token) {
    out << "[" << token->GetTypeAsString() << ", " << token->GetValueView() << "]";
    return out;
}
