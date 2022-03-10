//
// Created by ortur on 20.02.2022.
//
#include "lexer.h"
#include "rules.h"
#include "token_recognizer.h"

using namespace std;

vector<TokenPtr> SplitLineIntoTokens(const string& line, const grammar::Rules& rules) {

    vector<TokenPtr> result;
    result.reserve(16);

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
                        result.push_back(move(MakeToken(final_descision, move(subs))));
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


vector<TokenPtr> SplitTextIntoTokens(istream& in, const grammar::Rules& rules) {
    vector<TokenPtr> result;

    result.reserve(100);
    int line_number = 1;
    for (string line; getline(in, line);) {
            try {
                for (auto& token : SplitLineIntoTokens(line, rules)) {
                    result.push_back(move(token));
                }
                line_number++;
            } catch (std::exception& e) {
                cerr << "ERROR ON LINE: " << line_number << " " << e.what() << endl;
            }

    }

    return result;
}