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

    virtual void ParseFrom(TokenStream &stream) = 0;

    //virtual void GeneratePOLIZ() = 0;
    virtual ~Nonterminal() = default;

    const Type type;
};

using NontermHolder = std::shared_ptr<Nonterminal>;


namespace Nonterms {

    class Operator : public Nonterminal {
    public:

        enum class OpType {
            ADD,
            SUB,
            MUL,
            DIV,
        };

        Operator(OpType operation = OpType::ADD)
                : Nonterminal(Nonterminal::Type::OPERATOR), type(operation) {}

        std::string ToString() const override {

            static const std::unordered_map<OpType, std::string> TYPE_TO_STRING = {
                    {OpType::ADD, "+"},
                    {OpType::SUB, "-"},
                    {OpType::MUL, "*"},
                    {OpType::DIV, "/"},
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
            out << "RVALUE NONTERM: TYPE ->" << TYPE_TO_STRING.at(type);
            switch (type) {
                case ValType::INT_LITERAL : {
                    out << "VALUE -> "<< std::get<int>(value);
                } break;

                case ValType::STRING_LITERAL : {
                    out << "VALUE -> "<< std::get<std::string>(value);
                } break;
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

    private:
        std::string name;
    };

    class DataType : public Nonterminal {
    public:

        enum class Typename {
            INT,
        };

        DataType(Typename type = Typename::INT)
                : Nonterminal(Nonterminal::Type::TYPE_SPECIFIER), type(type) {}

        std::string ToString() const override {

            static const std::unordered_map<Typename, std::string> TYPE_TO_STRING = {
                    {Typename::INT, "Int"},
            };
            std::stringstream out;
            out << "TYPE_SPECIFIER NONTERM: VALUE ->" << TYPE_TO_STRING.at(type);
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
        }

    private:
        Typename type;
    };

    class VarDeclaration : public Nonterminal {

        VarDeclaration()
                : Nonterminal(Nonterminal::Type::VAR_DECLARATION) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "VAR_DECLARATION NONTERM: VAR_NAME ->"
                << var_name << std::endl
                << type.ToString();

            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
        }

    private:
        std::string var_name;
        DataType type;
    };

    class Assignable : public Nonterminal {
    public:

        enum class Type {
            LVALUE,
            DECLARATION
        };

        Assignable(Assignable::Type type = Type::LVALUE)
                : Nonterminal(Nonterminal::Type::ASSIGNABLE) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "ASSIGNABLE: " << std::endl
                << value->ToString();
            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
        }

    private:
        NontermHolder value;
    };

    class ValueExpression : public Nonterminal {
    public:
        ValueExpression()
                : Nonterminal(Nonterminal::Type::VALUE_EXPRESSION) {}

        std::string ToString() const override {
            std::stringstream out;

            out << "VALUE_EXPRESSION: " << std::endl;
            for (const auto &element: elements_) {
                out << element->ToString() << "\n";
            }

            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
        }

    private:
        std::vector<NontermHolder> elements_;
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

            out << "LANG: " << std::endl;

            for (auto &expr: expressions_) {
                out << expr.ToString() << std::endl;
            }

            return out.str();
        }

        void ParseFrom(TokenStream &stream) override {
        }

    private:
        std::vector<AssignExpression> expressions_;
    };

};