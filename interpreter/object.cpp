#include <iostream>

#include "object.h"

bool Int::HasSUMOperator() const {
    return true;
}

bool Int::HasDIVOperator() const {
    return true;
}

bool Int::HasMULOperator() const {
    return true;
}

bool Int::HasSUBOperator() const {
    return true;
}

std::size_t Int::Hash() const {
    return static_cast<size_t>(value_);
}

std::string Int::ToString() const {
    return std::to_string(value_);
}

void Int::Assign(ObjPtr other) {
    if (type != other->type) {
        throw std::runtime_error("Summing different types");
    }
    value_ = std::dynamic_pointer_cast<Int>(other)->value_;
}

std::ostream& operator<<(std::ostream& out, const Int& value) {
    out << value.value_;
    return out;
}

ObjPtr operator+(const ObjPtr& lhs, const ObjPtr& rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Summing different types");
    }

    if (!lhs->HasSUMOperator() || !rhs->HasSUMOperator()) {
        throw std::runtime_error("Doesnt have add operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT:
        {
            const auto& lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto& rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value + rhs_value);
            return result;
        } break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator-(const ObjPtr& lhs, const ObjPtr& rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Sub different types");
    }

    if (!lhs->HasSUMOperator() || !rhs->HasSUMOperator()) {
        throw std::runtime_error("Doesnt have sub operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT:
        {
            const auto& lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto& rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value - rhs_value);
            return result;
        } break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator*(const ObjPtr& lhs, const ObjPtr& rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Mul different types");
    }

    if (!lhs->HasSUMOperator() || !rhs->HasSUMOperator()) {
        throw std::runtime_error("Doesnt have mul operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT:
        {
            const auto& lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto& rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value * rhs_value);
            return result;
        } break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}

ObjPtr operator/(const ObjPtr& lhs, const ObjPtr& rhs) {

    if (lhs->type != rhs->type) {
        throw std::runtime_error("Div different types");
    }

    if (!lhs->HasSUMOperator() || !rhs->HasSUMOperator()) {
        throw std::runtime_error("Doesnt have add operator");
    }

    switch (lhs->type) {
        case Obj::Type::BASIC_INT:
        {
            const auto& lhs_value = std::dynamic_pointer_cast<Int>(lhs)->value_;
            const auto& rhs_value = std::dynamic_pointer_cast<Int>(rhs)->value_;
            ObjPtr result = std::make_shared<Int>(lhs_value / rhs_value);
            return result;
        } break;

        default : {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    }
}


ObjPtr MakeObj(Obj::Type type) {
    switch (type) {
        case Obj::Type::BASIC_INT: {
            return std::make_shared<Int>();
        } break;


    }
}