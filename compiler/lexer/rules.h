//
// Created by ortur on 20.02.2022.
//

#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H

#ifndef TESTING_MODE
#include "token.h"
#else
#include "../token/token.h"
#endif

#include <iostream>
#include <regex>



namespace grammar {

    struct Rule {
        TokenType type_;
        std::regex pattern_;
    };

    using Rules = std::vector<Rule>;

    //регулярки для дробления
    const Rules rulesV3 = {

            {TokenType::OPERATOR,       std::regex(R"([+\-*/=%&!]{1}|(==){1}|(\*\*){1}|(\-\-){1}|(\+\+){1})")},
            {TokenType::IDENTIFIER,     std::regex(R"([A-Za-z_]{1,})")},
            {TokenType::KEYWORD,        std::regex(R"((\bfor\b)|(\bif\b)|(\belse\b)|(\b:\b)|(\bload\b))")},
            {TokenType::NUMBER,         std::regex(R"(([\-]{0,1}([0]{0,})([0-9]*)))")},
            {TokenType::BRACKET,        std::regex(R"([\[\](){}<>]{1})")},
            {TokenType::SEPARATOR,      std::regex(R"([\t\s;,]{1,})")},
            {TokenType::STRING_LITERAL, std::regex(R"("(\\.|[^\\"])*")")},

    };
}

//grammar::Rules LoadRules(std::istream& in);

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H
