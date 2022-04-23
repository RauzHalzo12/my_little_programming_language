#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "profile.h"
#include "token.h"
#include "grammar.h"

std::string GetProgramText(std::istream &input) {
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

int main() {

    LOG_DURATION("TOTAL: ")

    std::ifstream input("parser_test.rtr");
    if (!input.is_open()) {
        std::cerr << "No FILE!" << std::endl;
        std::terminate();
    }

    std::string text = GetProgramText(input);
    input.close();
    TokenStream stream(SplitIntoTokens(text));

//    for (auto &token: SplitIntoTokens(text)) {
//        std::cout << token.value << " " << token.line_number << std::endl;
//    }

    NontermHolder lang = MakeNonterminal(Nonterminal::Type::LANG);
    LOG_DURATION("PARSE TIME:")
    lang->ParseFrom(stream);

    std::cout << lang->ToString();

    return 0;
}
