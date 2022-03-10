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
    LOG_DURATION("My pp is bigger")
   for (int i = 0; i < 50; i++) {
        ifstream source_file("src.pup");
        if (!source_file.is_open()) {
            cerr << "No file!";
        }
        SplitTextIntoTokens(source_file);

        source_file.close();
    }

    return 0;
}