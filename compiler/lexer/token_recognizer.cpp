#include "token_recognizer.h"

using namespace std;

TokenRecognizer::TokenRecognizer(const grammar::Rules& rules)
    : rules_(rules), last_matched_(TokenType::UNDEFINED), current_match_(TokenType::UNDEFINED) {

}

RecognitionResult TokenRecognizer::TryIdentify(std::string_view lexem) {
    last_matched_ = current_match_;
    RecognitionResult result = RecognitionResult::NONE;

    for (const auto& rule : rules_) {

        if (regex_match(lexem.data(), rule.pattern_)) {
            last_matched_ = current_match_;
            current_match_ = rule.type_;
            result = RecognitionResult::HAS_MATCHES;
            break;
        }
    }

    return result;
}

TokenType TokenRecognizer::GetLastIdentified() const {
    return last_matched_;
}

TokenType TokenRecognizer::GetCurrentMatch() const {
    return current_match_;
}

TokenType TokenRecognizer::MakeFinalDesision(bool is_end_of_line) const {
    if (is_end_of_line && current_match_ != TokenType::UNDEFINED)
        return current_match_;
    else
        return last_matched_;
}


void TokenRecognizer::Reset() {
    last_matched_ = TokenType::UNDEFINED;
    current_match_ = TokenType::UNDEFINED;
}