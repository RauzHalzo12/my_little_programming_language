#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_LEXER_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_LEXER_H

#include <deque>
#include "token.h"
#include "rules.h"

std::deque<TokenPtr> SplitLineIntoTokens(const std::string& line, const grammar::Rules& rules);

std::deque<TokenPtr> SplitTextIntoTokens(std::istream& in, const grammar::Rules& rules);

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_LEXER_H
