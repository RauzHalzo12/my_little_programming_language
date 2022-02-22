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
    ss << "for int i = 0 i ++ 6889889879789789789789789789789897909889897897897897897897898978998";
    for (auto& token : SplitTextIntoTokens(ss, grammar::proto_rules) ){
        cout << token << endl;
    }
    return 0;
}