#pragma once

#include <string>
#include <memory>

#include "virtual_machine.h"
#include "object.h"
#include "parsers/parsing_stuff.h"


struct Instruction;

using InstructionHolder = std::unique_ptr<Instruction>;

struct Instruction {

    enum class Type {
        ADD,
        MUL,
        DIV,
        SUB,
        ASN,
        CRT,
        PUSH,
    };

    Instruction(Type t) : type(t) {}

    static InstructionHolder Create(Type type);

    virtual void ParseFrom(std::string_view& input) = 0;

    virtual void Process(VirtualMachine &vm) = 0;

    virtual ~Instruction() = default;

    const Type type;
};


const std::unordered_map<std::string_view, Instruction::Type> STRING_TO_INSTRUCTION = {
        {"ADD", Instruction::Type::ADD},
        {"ASN", Instruction::Type::ASN},
        {"DIV", Instruction::Type::DIV},
        {"MUL", Instruction::Type::MUL},
        {"SUB", Instruction::Type::SUB},
        {"CRT", Instruction::Type::CRT},
        {"PUSH", Instruction::Type::PUSH},
};

struct AddInstruction : public Instruction {
    AddInstruction() : Instruction(Type::ADD) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs + rhs);
    }


    void ParseFrom(std::string_view& input) override {
        return;
    }

};

struct SubInstruction : public Instruction {
    SubInstruction() : Instruction(Type::SUB) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs - rhs);
    }

    void ParseFrom(std::string_view& input) override {
        return;
    }
};

struct MulInstruction : public Instruction {
    MulInstruction() : Instruction(Type::MUL) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs * rhs);
    }

    void ParseFrom(std::string_view& input) override {
        return;
    }
};

struct DivInstruction : public Instruction {
    DivInstruction() : Instruction(Type::DIV) {}

    void Process(VirtualMachine &vm) override {
        const auto &rhs = vm.Top();
        const auto &lhs = vm.Top();
        vm.Push(lhs / rhs);
    }

    void ParseFrom(std::string_view& input) override {
        return;
    }
};

struct CrtInstruction : public Instruction {
    CrtInstruction() : Instruction(Type::CRT) {}

    void Process(VirtualMachine &vm) override {

        vm.CreateVar(name,
                     MakeObj(STRING_TO_TYPE.at(type))
        );
    }

    void ParseFrom(std::string_view& input) override {
        name = ReadToken(input);
        type = ReadToken(input);
    }

    std::string name;
    std::string type;
};

struct PushInstruction : public Instruction {
    PushInstruction() : Instruction(Type::PUSH) {}

    void Process(VirtualMachine &vm) override {
        if (STRING_TO_TYPE.contains(first_token)) {
            auto obj_type = STRING_TO_TYPE.at(first_token);

            switch (obj_type) {
                case Obj::Type::BASIC_INT: {
                    ObjPtr result = std::make_shared<Int>(
                            std::atoi(second_token.c_str())
                    );

                    vm.Push(result);
                }
                    break;
            }

        } else {
            vm.Push(second_token);
        }
    }

    void ParseFrom(std::string_view& input) override {
        first_token = ReadToken(input);
        second_token = ReadToken(input);
    }

    std::string first_token;
    std::string second_token;

};

struct AsnInstruction : public Instruction {
    AsnInstruction() : Instruction(Type::ASN) {}

    void Process(VirtualMachine &vm) override {
        auto rhs = vm.Top();
        auto lhs = vm.Top();
        lhs->Assign(rhs);
    }

    void ParseFrom(std::string_view& input) override {
        return;
    }
};

InstructionHolder MakeInstruction(Instruction::Type type) {
    switch (type) {
        case Instruction::Type::DIV: {
            return std::make_unique<DivInstruction>();
        } break;

        case Instruction::Type::MUL: {
            return std::make_unique<MulInstruction>();
        } break;

        case Instruction::Type::ADD: {
            return std::make_unique<AddInstruction>();
        } break;

        case Instruction::Type::SUB: {
            return std::make_unique<SubInstruction>();
        } break;

        case Instruction::Type::ASN: {
            return std::make_unique<AsnInstruction>();
        } break;

        case Instruction::Type::PUSH: {
            return std::make_unique<PushInstruction>();
        } break;

        case Instruction::Type::CRT: {
            return std::make_unique<CrtInstruction>();
        } break;
    }
}



std::vector<InstructionHolder> ReadInstructions(std::istream& in = std::cin) {
    std::vector<InstructionHolder> result;

    for (std::string command; getline(in, command);) {
        std::string_view cmd_view = command;
        auto cmd_type = STRING_TO_INSTRUCTION.at(ReadToken(cmd_view));
        auto instruction = MakeInstruction(cmd_type);
        instruction->ParseFrom(cmd_view);
        result.push_back(std::move(instruction));
    }

    return result;
}


void ProcessInstructions(std::vector<InstructionHolder>&& instructions, VirtualMachine& vm) {
    for (auto& instr : instructions) {
        instr->Process(vm);
    }
}