
#include "test_runner.h"
#define  TESTING_MODE
#include "compiler/token/token.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/rules.h"

#include <fstream>


using namespace std;

void TestEmptyLine() {
    {
        string empty = "";

        auto result = SplitLineIntoTokens(empty, grammar::proto_rules);

        ASSERT_EQUAL(result.empty(), true);
    }

    {
        string empty = "                                                                                          ";

        auto result = SplitLineIntoTokens(empty, grammar::proto_rules);

        ASSERT_EQUAL(result.empty(), true);
    }

    {
        string empty = "   \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

        auto result = SplitLineIntoTokens(empty, grammar::proto_rules);

        ASSERT_EQUAL(result.empty(), true);
    }

}

void TestStream() {
    ifstream input_file("example1.txt");
    if (!input_file.is_open()) {
        cerr << "FILE NOT FOUND!" << endl;
    }
    for (auto& token : SplitTextIntoTokens(input_file, grammar::proto_rules)) {
        cout << token << endl;
    }
    input_file.close();

}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEmptyLine);
    RUN_TEST(tr, TestStream);
    return 0;
}
