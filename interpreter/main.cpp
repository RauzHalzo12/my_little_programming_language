#include <iostream>
#include "interpreter.h"
#include "variable.h"
#include <boost/any.hpp>
#include <any>
#include <stack>

using namespace std;

int main() {
    std::stack<std::shared_ptr<BasicValue>> anys;

    anys.push(std::make_shared<BasicInt>(21342));
    anys.push(std::make_shared<BasicString>("abooba"s));
    anys.push(std::make_shared<BasicString>("zzzz"s));

    while (!anys.empty()) {
        std::cout << anys.top()->ToString() << std::endl;
        anys.pop();
    }
    return 0;
}

