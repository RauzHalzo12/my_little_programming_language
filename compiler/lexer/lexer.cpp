//
// Created by ortur on 20.02.2022.
//
#include "lexer.h"
#include "rules.h"
#include "token_recognizer.h"

using namespace std;

class Buffer {
public:
    Buffer(const Buffer &) = delete;

    const Buffer &operator=(const Buffer &) = delete;

    Buffer(size_t capacity) : capacity_(capacity), data_(new char[capacity]) {}

    Buffer &operator<<(char symbol) {
        if (size_ + 1 <= capacity_) {
            data_[size_++] = symbol;
        }
        return *this;
    }

    string GetPrefix(size_t prefix_size) const {
        return string(data_, prefix_size);
    }

    string ToString() const {
        return string(data_, size_);
    }

    size_t GetSize() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

    void Clear() {
        size_ = 0;
    }

    ~Buffer() {
        if (data_)
            delete[] data_;
    }

private:
    const size_t capacity_;
    size_t size_ = 0;
    char *data_;
};



vector<TokenPtr> SplitTextIntoTokens(istream& in, const grammar::Rules &rules) {
    vector<TokenPtr> result;

    enum class RecognitionState {
        WAITING_FOR_SUCCESS,
        WAITING_FOR_UNSUCCESS,
    };

    RecognitionState current_state = RecognitionState::WAITING_FOR_SUCCESS;
    Buffer symbols(256);
    char curr;
    TokenRecognizer tr(rules);

    while (in >> std::noskipws >> curr) {
        symbols << curr;

        auto descision = tr.TryIdentify(std::move(symbols.ToString()));

        if (descision == RecognitionResult::HAS_MATCHES) {
            if (current_state == RecognitionState::WAITING_FOR_SUCCESS) {
                current_state = RecognitionState::WAITING_FOR_UNSUCCESS;
            }
        } else {

            if (current_state == RecognitionState::WAITING_FOR_UNSUCCESS) {

                if (tr.GetLastIdentified() != TokenType::SEPARATOR) {
                    result.push_back(std::move(
                            MakeToken(
                                    tr.GetLastIdentified(),
                                    std::move(symbols.GetPrefix(symbols.GetSize() - 1))
                            )
                    ));
                }


                current_state = RecognitionState::WAITING_FOR_SUCCESS;

                symbols.Clear();
                symbols << curr;


                if (tr.TryIdentify(symbols.ToString()) == RecognitionResult::HAS_MATCHES) {
                    current_state = RecognitionState::WAITING_FOR_UNSUCCESS;
                }
            }
        }

    }


    if (!symbols.Empty()) {
        result.push_back(std::move(
                MakeToken(
                        tr.GetCurrentMatch(),
                        std::move(symbols.ToString())
                )));
    }

    return result;
}