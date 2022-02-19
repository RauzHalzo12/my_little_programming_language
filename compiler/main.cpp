//
// Created by ortur on 19.02.2022.
//

#include <iostream>
#include "token/token.h"


int main() {
    auto token = MakeToken(TokenType::OPERATOR, "+");
    std::cout << token;
    return 0;
}