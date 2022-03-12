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


#include <boost/regex.hpp>
//#include <regex>



namespace grammar {

    struct Rule {
        TokenType type_;
        boost::regex pattern_;
    };

    using Rules = std::vector<Rule>;

    //регулярки для дробления
    const Rules rulesV3 = {
            {TokenType::KEYWORD,        boost::regex(R"((\bfor\b)|(\bif\b)|(\belse\b)|(\b:\b)|(\bload\b))")},
            {TokenType::OPERATOR,       boost::regex(R"([+\-*/=%&!]{1}|(==){1}|(\*\*){1}|(\-\-){1}|(\+\+){1})")},
            {TokenType::IDENTIFIER,     boost::regex(R"([A-Za-z_]{1,})")},
            {TokenType::NUMBER,         boost::regex(R"(([\-]{0,1}([0]{0,})([0-9]*)))")},
            {TokenType::BRACKET,        boost::regex(R"([\[\](){}<>]{1})")},
            {TokenType::SEPARATOR,      boost::regex(R"([\t\s;,]{1,})")},
            {TokenType::STRING_LITERAL, boost::regex(R"("(\\.|[^\\"])*")")},
    };
}

//grammar::Rules LoadRules(std::istream& in);

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_RULES_H
