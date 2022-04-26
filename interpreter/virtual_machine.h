#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stack>

#include "object.h"

class VirtualMachine {
public:

    VirtualMachine();
    VirtualMachine(const VirtualMachine&) = delete;
    VirtualMachine& operator=(const VirtualMachine&) = delete;
    ~VirtualMachine();

    void CreateVar(const std::string& name, ObjPtr value);
    void Push(ObjPtr value);
    void Push(const std::string& varname);

    ObjPtr Top();

    const std::unordered_map<std::string, ObjPtr>& GetResults() const;

    void Run();


private:
//    std::ifstream in_;
//    std::ofstream out_;
//    std::ofstream err_;

    std::unordered_map<std::string, ObjPtr> var_map_;
    std::stack<ObjPtr> run_stack_;
};
