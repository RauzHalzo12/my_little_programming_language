#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_LEXER_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_LEXER_H

#include <deque>

#ifndef TESTING_MODE
#include "token.h"
#else
#include "../token/token.h"
#endif

#include "rules.h"

std::vector<TokenPtr> SplitTextIntoTokens(std::istream& in, const grammar::Rules& rules = grammar::rulesV3);


#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_LEXER_H
