#include <iostream>
#include "virtual_machine.h"
#include "instructions.h"
#include "profile.h"

using namespace std;

int main() {

    std::ifstream code("../compiler/out.irp");
    VirtualMachine vm;
    {
        LOG_DURATION("TOTAL:" );
        ProcessInstructions(ReadInstructions(code), vm);
    }

    for (auto& [key, val] : vm.GetResults()) {
        std::cout << key << " - " << val->ToString() << std::endl;
    }

    code.close();

    return 0;

}

