//
// Created by ortur on 19.02.2022.
//

#include <iostream>

#include "token.h"
#include "lexer.h"
#include "rules.h"


using namespace std;

int main() {
    stringstream ss;
    ss << "@size - = fi 1";
    //auto result = SplitTextIntoTokens(ss, grammar::proto_rules);
    for (auto& token : SplitTextIntoTokens(ss, grammar::proto_rules) ){
        cout << token << endl;
    }
    return 0;
}