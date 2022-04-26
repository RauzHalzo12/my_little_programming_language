#include <iostream>

#include <stack>

#include "object.h"
#include "virtual_machine.h"
#include "instructions.h"

using namespace std;

int main() {

    std::ifstream code("../compiler/out.irp");
    VirtualMachine vm;

    ProcessInstructions(ReadInstructions(code), vm);

    for (auto& [key, val] : vm.GetResults()) {
        std::cout << key << " - " << val->ToString() << std::endl;
    }

    code.close();


    return 0;
}

