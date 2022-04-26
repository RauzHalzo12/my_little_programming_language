#include <iostream>
#include <sstream>
#include "virtual_machine.h"

VirtualMachine::VirtualMachine() {
    //    : in_(input_path), out_("out.txt"), err_("errors.txt") {

//    if (!in_.is_open()) {
//        throw std::runtime_error("no code!");
//    }

}

VirtualMachine::~VirtualMachine() {
//    in_.close();
//    out_.close();
//    err_.close();
}

void VirtualMachine::Run() {
//    for (std::string line; getline(in_, line);) {
//    }
}

void VirtualMachine::CreateVar(const std::string &name, ObjPtr value) {
    if (var_map_.contains(name)) {
        std::stringstream error;
        error << "Already have variable with this name" << std::endl;
        throw std::runtime_error(error.str());
    }
    var_map_[name] = value;
}

void VirtualMachine::Push(ObjPtr value) {
    run_stack_.push(value);
}

void VirtualMachine::Push(const std::string &varname) {
    if (!var_map_.contains(varname)) {
        std::stringstream error;
        error << "Doesn't exist" << std::endl;
        throw std::runtime_error(error.str());
    }
    run_stack_.push(var_map_[varname]);
}


const std::unordered_map<std::string, ObjPtr>&
VirtualMachine::GetResults() const {
    return var_map_;
}

ObjPtr VirtualMachine::Top() {
    auto result = run_stack_.top();
    run_stack_.pop();
    return result;
}
