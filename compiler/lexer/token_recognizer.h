//
// Created by Artur on 20.02.2022.
//

#ifndef MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_RECOGNIZER_H
#define MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_RECOGNIZER_H

#include "rules.h"

enum class RecognitionResult {
    NONE,
    HAS_MATCHES,
};

class TokenRecognizer {
public:

    explicit TokenRecognizer(const grammar::Rules& rules);

    RecognitionResult TryIdentify(std::string_view lexem);

    TokenType GetLastIdentified() const;

    TokenType GetCurrentMatch() const;

    TokenType MakeFinalDesision(bool is_end_of_line) const;

    void Reset();

private:

    const grammar::Rules& rules_;
    TokenType last_matched_;
    TokenType current_match_;
};

#endif //MY_LITTLE_PROGRAMMING_LANGUAGE_TOKEN_RECOGNIZER_H
