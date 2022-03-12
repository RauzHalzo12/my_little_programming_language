//
// Created by ortur on 19.02.2022.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "token.h"

#include "lexer.h"
#include "rules.h"
#include "benchmark_libs/profile.h"

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    LOG_DURATION("TOTAL:")

        ifstream source_file("src.pup");
        if (!source_file.is_open()) {
            cerr << "No file!";
        }

        for (auto& token : SplitTextIntoTokens(source_file)) {
            cout << token << endl;
        }

        source_file.close();


    return 0;
}