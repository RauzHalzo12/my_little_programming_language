
#include "test_runner.h"

#include "compiler/token/token.h"

#include <string>

using namespace std;


void TestConstruction() {

   auto construct = [](TokenType type, const string& message) {
        TokenPtr token = MakeToken(type, message);
        ASSERT_EQUAL(static_cast<int>(token->GetType()), static_cast<int>(type));
        ASSERT_EQUAL(token->GetValueView(), message);
    };

    construct(TokenType::UNDEFINED, "undef");
    construct(TokenType::OPERATOR, "op");
    construct(TokenType::KEYWORD, "key");
    construct(TokenType::LITERAL, "literal");
    construct(TokenType::IDENTIFIER, "id");
    construct(TokenType::SEPARATOR, "sep");

}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConstruction);
    return 0;
}
