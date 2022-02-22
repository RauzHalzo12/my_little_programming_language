//
// Created by ortur on 20.02.2022.
//

#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H

#include "token.h"

#include <iostream>
#include <regex>



namespace grammar {

    struct Rule {
        TokenType type_;
        std::regex pattern_;
    };

    using Rules = std::vector<Rule>;

    //регулярки для дробления
    const Rules proto_rules = {
            {TokenType::IDENTIFIER, std::regex(R"([A-Za-z]{1,})")},
            {TokenType::OPERATOR, std::regex(R"([+\-*/=]{1})")},
            {TokenType::KEYWORD, std::regex(R"((\bfor\b)|(\bif\b)|(\belse\b))")},
            {TokenType::LITERAL, std::regex(R"([0-9]{1,})")},
            {TokenType::SEPARATOR, std::regex(R"([\s]{1,})")},
    };
}

//grammar::Rules LoadRules(std::istream& in);

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H