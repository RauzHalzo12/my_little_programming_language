//
// Created by ortur on 20.02.2022.
//
#include "lexer.h"
#include "rules.h"
#include "token_recognizer.h"

using namespace std;

deque<TokenPtr> SplitLineIntoTokens(const string& line, const grammar::Rules& rules) {
    deque<TokenPtr> result;

    TokenRecognizer recognizer(rules);

    for (size_t l = 0; l < line.size();) {
        size_t r = l+1;
        for (; r <= line.size(); r++) {
            auto subs = line.substr(l, r - l);

            auto state = recognizer.TryIdentify(subs);

            if (state == RecognitionResult::NONE) {


                auto final_descision = recognizer.GetLastIdentified();

                if (final_descision == TokenType::UNDEFINED) {
                    throw runtime_error("invalid symbol was used!");
                }

                if (final_descision != TokenType::SEPARATOR) {
                    result.push_back(move(
                            MakeToken(final_descision,
                                      move(line.substr(l, r - l - 1)))
                    ));
                }

                l = r - 1;

                recognizer.Reset();
                break;

            } else {

                if (r == line.size()) {
                    auto final_descision = recognizer.GetCurrentMatch();

                    if (final_descision == TokenType::UNFINISHED_STRING_LITERAL) {
                        throw runtime_error("has unfinished string literal!");
                    }

                    if (final_descision != TokenType::UNDEFINED && final_descision != TokenType::SEPARATOR) {
                        result.push_back(move(MakeToken(final_descision, subs)));
                    }

                    l = r;
                    break;
                }

                continue;
            }

        }
    }

    return result;
}


deque<TokenPtr> SplitTextIntoTokens(istream& in, const grammar::Rules& rules) {
    deque<TokenPtr> result;

    for (string line; getline(in, line);) {
        for (auto& token : SplitLineIntoTokens(line, rules)) {
            result.push_back(move(token));
        }
    }

    return result;
}