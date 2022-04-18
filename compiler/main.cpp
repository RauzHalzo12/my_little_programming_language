#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "profile.h"
#include <vector>
#include "token.h"
#include "grammar.h"


std::string GetProgrammText(std::istream& input) {
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

int main() {
//    std::ofstream out("parser_test.rtr");
//    out.close();
    LOG_DURATION("TOTAL: ")

    std::ifstream input("parser_test.rtr");
    if (!input.is_open()) {
        std::cerr << "No FILE!" << std::endl;
        std::terminate();
    }

    std::string text = GetProgrammText(input);
    input.close();

    for (auto& token : SplitIntoTokens(text)) {
        std::cout << token.value << " " << token.line_number << std::endl;
    }


    TokenStream stream(SplitIntoTokens(text));


    while (stream.HasCurrent()) {
        NontermHolder op = std::make_shared<Nonterms::RValue>();
        op->ParseFrom(stream);
        std::cout << op->ToString() << std::endl;
    }


    //Parser parser(stream);



    return 0;
}
