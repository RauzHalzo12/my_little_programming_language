
#include "test_runner.h"
#define  TESTING_MODE
#include "compiler/token/token.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/rules.h"

using namespace std;

void TestEmpty() {
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


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEmpty);
    return 0;
}
