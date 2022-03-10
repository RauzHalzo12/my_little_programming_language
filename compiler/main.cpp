//
// Created by ortur on 19.02.2022.
//

#include <iostream>

#include "token.h"
#include "lexer.h"
#include "rules.h"

#include <fstream>
#include <ctime>
#include "profile.h"


using namespace std;

int main() {

    ofstream out("input.txt", ios::app);
    out.close();
//    {
//        LOG_DURATION("LEXICAL ANALYS TIME: ");
//        for (int i = 0; i < 50; i++) {
//            ifstream input("input.txt");
//            SplitTextIntoTokens(input, grammar::proto_rules);
//            input.close();
//        }
//    }
    LOG_DURATION("TOTAL: ")
    for (int i = 0; i < 50; i++ ){
        ifstream input("input.txt");
        SplitTextIntoTokens(input, grammar::proto_rules);
        input.close();
    }





    return 0;
}