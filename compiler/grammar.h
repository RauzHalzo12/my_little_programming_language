#pragma once

#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "token.h"


struct Nonterminal {

    enum class Type {
        ASSIGN_EXPRESSION,
        VALUE_EXPRESSION,
        VAR_DECLARATION,
        LVALUE,
        RVALUE,
        ASSIGNABLE,
        TYPE_SPECIFIER,
        OPERATOR,
        LANG,
    };

    Nonterminal() = default;

    Nonterminal(Type type) : type(type) {}

    virtual std::string ToString() const = 0;

    virtual void GenerateRPN(std::ostream &out) const = 0;

    virtual void ParseFrom(TokenStream &stream) = 0;

    virtual ~Nonterminal() = default;

    const Type type;
};

using NontermHolder = std::shared_ptr<Nonterminal>;

NontermHolder MakeNonterminal(Nonterminal::Type type);

namespace Nonterminals {

    class Operator : public Nonterminal {
    public:

        enum class OpType {
            ADD,
            SUB,
            MUL,
            DIV,
            OPARENTH,
            CPARENTH,
        };

        Operator(OpType operation = OpType::ADD)
                : Nonterminal(Nonterminal::Type::OPERATOR), type(operation) {}

        std::string ToString() const override {

            static const std::unordered_map<OpType, std::string> TYPE_TO_STRING = {
                    {OpType::ADD,      "+"},
                    {OpType::SUB,      "-"},
                    {OpType::MUL,      "*"},
                    {OpType::DIV,      "/"},
                    {OpType::OPARENTH, "("},
                    {OpType::CPARENTH, ")"},
            };

            std::stringstream out;
            out << "OPERATION NONTERM: VALUE ->" << TYPE_TO_STRING.at(type);
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
            const Token &current_token = stream.GetCurrentToken();

            switch (current_token.type) {
                case Token::Type::ADD_OPERATOR: {
                    type = OpType::ADD;
                }
                    break;
                case Token::Type::SUB_OPERATOR: {
                    type = OpType::SUB;
                }
                    break;
                case Token::Type::DIV_OPERATOR: {
                    type = OpType::DIV;
                }
                    break;
                case Token::Type::MUL_OPERATOR: {
                    type = OpType::MUL;
                }
                    break;
                case Token::Type::OPEN_PARENTHESIS: {
                    type = OpType::OPARENTH;
                }
                    break;
                case Token::Type::CLOSE_PARENTHESIS: {
                    type = OpType::CPARENTH;
                }
                    break;
                default: {
                    std::stringstream error;
                    error << "Expected operator, but have -> " << current_token.value
                          << " on line " << current_token.line_number << std::endl;
                    throw std::runtime_error(error.str());
                }

            }
            stream.MoveToNextToken();
        }

        OpType GetType() const {
            return type;
        }

        void GenerateRPN(std::ostream &out) const override {

            switch (type) {
                case OpType::ADD: {out << "ADD " << std::endl;} break;
                case OpType::MUL: {out << "MUL " << std::endl;} break;
                case OpType::DIV: {out << "DIV " << std::endl;} break;
                case OpType::SUB: {out << "SUB " << std::endl;} break;
                default: {
                    return;
                } break;
            }

        }

    private:
        OpType type;
    };

    class RValue : public Nonterminal {
    public:
        enum class ValType {
            INT_LITERAL,
            STRING_LITERAL,
        };

        RValue() : Nonterminal(Nonterminal::Type::RVALUE) {}

        std::string ToString() const override {
            static const std::unordered_map<ValType, std::string> TYPE_TO_STRING = {
                    {ValType::INT_LITERAL,    "INTEGER"},
                    {ValType::STRING_LITERAL, "STRING: "},
            };

            std::stringstream out;
            out << "RVALUE NONTERM: TYPE ->" << TYPE_TO_STRING.at(type) << "\t";
            switch (type) {
                case ValType::INT_LITERAL : {
                    out << "VALUE -> " << std::get<int>(value);
                }
                    break;

                case ValType::STRING_LITERAL : {
                    out << "VALUE -> " << std::get<std::string>(value);
                }
                    break;
            }
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
            const auto &current_token = stream.GetCurrentToken();

            switch (current_token.type) {
                case Token::Type::STRING_CONSTANT: {
                    type = ValType::STRING_LITERAL;
                    value.emplace<std::string>(current_token.value);
                }
                    break;
                case Token::Type::NUMBER_CONSTANT : {
                    type = ValType::INT_LITERAL;
                    value.emplace<int>(std::stoi(current_token.value));
                }
                    break;
                default: {
                    std::stringstream error;
                    error << "Expected rvalue, but have -> " << current_token.value
                          << " on line " << current_token.line_number << std::endl;
                    throw std::runtime_error(error.str());
                }
            }

            stream.MoveToNextToken();
        }

        void GenerateRPN(std::ostream &out) const override {
            if (std::holds_alternative<int>(value)) {
                out << "PUSH Int " << std::get<int>(value) << std::endl;
            } else {
                out << "PUSH String " << std::get<std::string>(value) << std::endl;
            }
        }

    private:
        ValType type;
        std::variant<int, std::string> value;
    };

    class LValue : public Nonterminal {
    public:
        LValue() : Nonterminal(Nonterminal::Type::LVALUE) {}

        std::string ToString() const override {
            std::stringstream out;
            out << "LVALUE NONTERM: NAME ->" << name;
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {

            if (!stream.HasCurrent()) {
                std::stringstream error;
                error << "Expected LValue";
                throw std::runtime_error(error.str());
            }

            const auto &current_token = stream.GetCurrentToken();

            if (current_token.type == Token::Type::VAR_NAME || current_token.type == Token::Type::IDENTIFIER) {

                name = current_token.value;
                stream.MoveToNextToken();

            } else {
                std::stringstream error;
                error << "Expected LValue, but have ->" << current_token.value
                      << " on line " << current_token.line_number;
                throw std::runtime_error(error.str());
            }
        }

        void GenerateRPN(std::ostream &out) const override {
            out << "PUSH Var " << name << std::endl;
        }

        std::string GetName() const {
            return name;
        }

    private:
        std::string name;
    };

    class DataType : public Nonterminal {
    public:

        enum class Typename {
            INT,
            STRING,
        };

        DataType(Typename type = Typename::INT)
                : Nonterminal(Nonterminal::Type::TYPE_SPECIFIER), type(type) {}

        std::string ToString() const override {

            static const std::unordered_map<Typename, std::string> TYPE_TO_STRING = {
                    {Typename::INT,    "Int"},
                    {Typename::STRING, "String"},
            };

            std::stringstream out;
            out << "TYPE_SPECIFIER NONTERM: VALUE ->" << TYPE_TO_STRING.at(type);
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
            if (!stream.HasCurrent()) {
                std::stringstream error;
                error << "Expected TypeSpecifier";
                throw std::runtime_error(error.str());
            }

            const auto &current_token = stream.GetCurrentToken();

            const static std::unordered_map<Token::Type, Typename> types = {
                    {Token::Type::BASIC_STRING, Typename::STRING},
                    {Token::Type::BASIC_INT,    Typename::INT},
            };

            if (types.contains(current_token.type)) {
                type = types.at(current_token.type);
                stream.MoveToNextToken();
            } else {
                std::stringstream error;
                error << "Expected type-specifier, but have -> " << current_token.value
                      << " on line " << current_token.line_number << std::endl;
                throw std::runtime_error(error.str());
            }

        }


        void GenerateRPN(std::ostream &out) const override {
            static const std::unordered_map<Typename, std::string> TYPE_TO_STRING = {
                    {Typename::INT,    "Int"},
                    {Typename::STRING, "String"},
            };
            out << TYPE_TO_STRING.at(type);
        }

    private:

        Typename type;
    };

    class VarDeclaration : public Nonterminal {
    public:
        VarDeclaration()
                : Nonterminal(Nonterminal::Type::VAR_DECLARATION) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "VAR_DECLARATION NONTERM: \n"
                << "\n" << value.ToString() << "\n" << type.ToString();

            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
            if (!stream.HasCurrent()) {
                std::stringstream error;
                error << "Expected VarDeclaration";
                throw std::runtime_error(error.str());
            }

            const auto &current_token = stream.GetCurrentToken();

            if (current_token.type == Token::Type::VAR_KEYWORD) {
                stream.MoveToNextToken();

                value.ParseFrom(stream);
                type.ParseFrom(stream);
            } else {
                std::stringstream error;
                error << "Expected var-declarationr, but have -> " << current_token.value
                      << " on line " << current_token.line_number << std::endl;
                throw std::runtime_error(error.str());
            }
        }

        void GenerateRPN(std::ostream &out) const override {

            out << "CRT ";
            out << value.GetName();
            out << " ";
            type.GenerateRPN(out);
            out << std::endl;

            value.GenerateRPN(out);
        }

    private:
        LValue value;
        DataType type;
    };

    class Assignable : public Nonterminal {
    public:

        Assignable()
                : Nonterminal(Nonterminal::Type::ASSIGNABLE) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "ASSIGNABLE: " << std::endl;

            if (std::holds_alternative<VarDeclaration>(value_)) {
                out << std::get<VarDeclaration>(value_).ToString();
            } else {
                out << std::get<LValue>(value_).ToString();
            }

            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
            if (!stream.HasCurrent()) {
                std::stringstream error;
                error << "Expected VarDeclaration";
                throw std::runtime_error(error.str());
            }

            const auto &current_token = stream.GetCurrentToken();

            switch (current_token.type) {
                case Token::Type::IDENTIFIER:
                case Token::Type::VAR_NAME: {
                    value_.emplace<LValue>();
                    std::get<LValue>(value_).ParseFrom(stream);
                }
                    break;
                case Token::Type::VAR_KEYWORD: {
                    value_.emplace<VarDeclaration>();
                    std::get<VarDeclaration>(value_).ParseFrom(stream);
                }
                    break;
                default : {
                    std::stringstream error;
                    error << "Expected assignable, but have -> " << current_token.value
                          << " on line " << current_token.line_number << std::endl;
                    throw std::runtime_error(error.str());
                }
            }
        }

        void GenerateRPN(std::ostream &out) const override {
            if (std::holds_alternative<VarDeclaration>(value_)) {
                std::get<VarDeclaration>(value_).GenerateRPN(out);
            } else {
                std::get<LValue>(value_).GenerateRPN(out);
            }
        }

    private:
        std::variant<LValue, VarDeclaration> value_;
    };

    class ValueExpression : public Nonterminal {
    public:
        ValueExpression()
                : Nonterminal(Nonterminal::Type::VALUE_EXPRESSION) {}

        std::string ToString() const override {
            std::stringstream out;
            for (const auto &val: result) {
                out << val->ToString() << std::endl;
                out << "=============================" << std::endl;
            }
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {

            // Алгоритм перевода выражений в ПолИЗ
            using TokType = Token::Type;
            using NtType = Nonterminal::Type;
            std::stack<NontermHolder> frames;

            while (stream.HasCurrent()) {

                const auto &current_token = stream.GetCurrentToken();

                switch (current_token.type) {

                    case TokType::NUMBER_CONSTANT:
                    case TokType::STRING_CONSTANT: {
                        NontermHolder rval = MakeNonterminal(NtType::RVALUE);
                        rval->ParseFrom(stream);
                        result.push_back(rval);
                    }
                        break;

                    case TokType::IDENTIFIER:
                    case TokType::VAR_NAME: {
                        NontermHolder lval = MakeNonterminal(NtType::LVALUE);
                        lval->ParseFrom(stream);
                        result.push_back(lval);
                    }
                        break;

                    case TokType::OPEN_PARENTHESIS: {
                        NontermHolder lbrace = MakeNonterminal(NtType::OPERATOR);
                        lbrace->ParseFrom(stream);
                        frames.push(lbrace);
                    }
                        break;

                    case TokType::CLOSE_PARENTHESIS: {

                        NontermHolder rbrace = MakeNonterminal(NtType::OPERATOR);
                        rbrace->ParseFrom(stream);

                        while (
                                !frames.empty()
                                && (
                                        std::dynamic_pointer_cast<Operator>(frames.top())->GetType() !=
                                        Operator::OpType::OPARENTH
                                )
                                ) {
                            //std::cerr << frames.top()->ToString() << std::endl;
                            result.push_back(frames.top());
                            frames.pop();
                        }


                        if (!frames.empty()
                            && std::dynamic_pointer_cast<Nonterminals::Operator>(frames.top())->GetType() ==
                               Operator::OpType::OPARENTH) {
                            frames.pop();
                        }


                    }
                        break;

                    case TokType::MUL_OPERATOR:
                    case TokType::DIV_OPERATOR: {

                        NontermHolder oper = MakeNonterminal(NtType::OPERATOR);
                        oper->ParseFrom(stream);
                        frames.push(oper);
                    }
                        break;

                    case TokType::ADD_OPERATOR:
                    case TokType::SUB_OPERATOR: {

                        NontermHolder oper = MakeNonterminal(NtType::OPERATOR);
                        oper->ParseFrom(stream);

                        if (frames.empty()
                            || std::dynamic_pointer_cast<Operator>(frames.top())->GetType() ==
                               Operator::OpType::OPARENTH) {
                            frames.push(oper);
                        } else {

                            while (
                                    !frames.empty()
                                    && (
                                            std::dynamic_pointer_cast<Operator>(frames.top())->GetType() ==
                                            Operator::OpType::MUL
                                            || std::dynamic_pointer_cast<Operator>(frames.top())->GetType() ==
                                               Operator::OpType::DIV
                                            || std::dynamic_pointer_cast<Operator>(frames.top())->GetType() !=
                                               Operator::OpType::OPARENTH

                                    )
                                    ) {
                                //std::cerr << frames.top()->ToString() << std::endl;
                                result.push_back(frames.top());
                                frames.pop();
                            }

                            frames.push(oper);
                        }

                    }
                        break;

                    case TokType::SEMICOLON: {
                        while (!frames.empty()) {
                            result.push_back(frames.top());
                            frames.pop();
                        }
                        stream.MoveToNextToken();
                        return;
                    }
                        break;

                    default : {
                        std::stringstream out;
                        out << "Invalid token: " << stream.GetCurrentToken().value
                            << " on line -> " << stream.GetCurrentToken().line_number << std::endl;
                        throw std::runtime_error(out.str());
                    }


                }

            }

            stream.MoveToNextToken();
        }


        void GenerateRPN(std::ostream &out) const override {

            for (auto &nonterm: result) {
                nonterm->GenerateRPN(out);

            }
        }

    private:
        std::vector<NontermHolder> result;
    };

    class AssignExpression : public Nonterminal {
    public:
        AssignExpression()
                : Nonterminal(Nonterminal::Type::ASSIGN_EXPRESSION) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "ASSIGN_EXPRESSION: " << std::endl
                << lhs.ToString() << " " << std::endl
                << rhs.ToString();
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {

            if (!stream.HasCurrent()) {
                std::stringstream error;
                error << "Expected VarDeclaration";
                throw std::runtime_error(error.str());
            }

            lhs.ParseFrom(stream);

            const auto &assign_token = stream.GetCurrentToken();

            if (assign_token.type != Token::Type::ASSIGN_OPERATOR) {
                std::stringstream error;
                error << "Expected ASSIGN OPERATOR, but have -> "
                      << assign_token.value << " on line " << assign_token.line_number;
                throw std::runtime_error(error.str());
            }

            stream.MoveToNextToken();

            rhs.ParseFrom(stream);
        }


        void GenerateRPN(std::ostream &out) const override {
            lhs.GenerateRPN(out);
            rhs.GenerateRPN(out);
            out << "ASN" << std::endl;
        }

    private:
        Assignable lhs;
        ValueExpression rhs;
    };

    class Lang : public Nonterminal {
    public:
        Lang() : Nonterminal(Nonterminal::Type::LANG) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "LANG: " << std::endl
                << "==========================" << std::endl;

            for (auto &expr: expressions_) {
                out << expr->ToString() << std::endl;
                out << "*****************************************" << std::endl;
            }

            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
            while (stream.HasCurrent()) {
                NontermHolder expr = MakeNonterminal(Nonterminal::Type::ASSIGN_EXPRESSION);
                expr->ParseFrom(stream);
                expressions_.push_back(expr);

            }
        }


        void GenerateRPN(std::ostream &out) const override {
            for (const auto &expr: expressions_) {
                expr->GenerateRPN(out);
            }
        }

    private:
        std::vector<NontermHolder> expressions_;
    };
};

NontermHolder MakeNonterminal(Nonterminal::Type type) {
    using nt = Nonterminal::Type;
    switch (type) {
        case nt::TYPE_SPECIFIER: {
            return std::make_shared<Nonterminals::DataType>();
        }
            break;
        case nt::VAR_DECLARATION: {
            return std::make_shared<Nonterminals::VarDeclaration>();
        }
            break;

        case nt::VALUE_EXPRESSION: {
            return std::make_shared<Nonterminals::ValueExpression>();
        }
            break;

        case nt::LVALUE: {
            return std::make_shared<Nonterminals::LValue>();
        }
            break;
        case nt::RVALUE: {
            return std::make_shared<Nonterminals::RValue>();
        }
            break;
        case nt::LANG: {
            return std::make_shared<Nonterminals::Lang>();
        }
            break;
        case nt::OPERATOR: {
            return std::make_shared<Nonterminals::Operator>();
        }
            break;
        case nt::ASSIGNABLE: {
            return std::make_shared<Nonterminals::Assignable>();
        }
            break;
        case nt::ASSIGN_EXPRESSION: {
            return std::make_shared<Nonterminals::AssignExpression>();
        }
            break;

        default: {
            throw std::runtime_error("bad nonterm type");
        }

    }
}