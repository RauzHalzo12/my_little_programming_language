#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "profile.h"

#include "token.h"

std::string GetProgrammText(std::istream& input) {
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}


int main() {


//    std::ofstream out("o.rtr");
//    out.close();
    std::ifstream input("o.rtr");

    LOG_DURATION("TOTAL: ")


    if (!input.is_open()) {
        std::cerr << "No FILE!" << std::endl;
        std::terminate();
    }

    std::string text = GetProgrammText(input);
    for (auto& token : SplitIntoTokens(text)) {
        std::cout << "[" << token.value << "]" << std::endl;
    };

    input.close();
    return 0;
}
