
#include "test_runner.h"

#include "compiler/token/token.h"


void TestEmpty() {

}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEmpty);
    return 0;
}
