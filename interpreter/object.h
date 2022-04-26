#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

struct Obj;

using ObjPtr = std::shared_ptr<Obj>;

struct Obj {

    enum class Type {
        BASIC_INT,
        BASIC_STRING,
    };

    explicit Obj(Type t) : type(t) {}

    virtual std::string ToString() const = 0;

    virtual bool HasSUMOperator() const = 0;

    virtual bool HasDIVOperator() const = 0;

    virtual bool HasMULOperator() const = 0;

    virtual bool HasSUBOperator() const = 0;

    virtual std::size_t Hash() const = 0;

    virtual ~Obj() = default;

    virtual void Assign(ObjPtr other) = 0;

    const Type type;
};


class Int : public Obj {
public:
    explicit Int(int value = 0) : Obj(Type::BASIC_INT), value_(value) {}

    bool HasSUMOperator() const override;
    bool HasDIVOperator() const override;
    bool HasMULOperator() const override;
    bool HasSUBOperator() const override;

    std::size_t Hash() const override;
    std::string ToString() const override;

    void Assign(ObjPtr other) override;

    friend std::ostream& operator<<(std::ostream& out, const Int& value);

    friend ObjPtr operator+(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator-(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator/(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator*(const ObjPtr& lhs, const ObjPtr& rhs);

private:
    int value_; // заменить на BigInt. Давайте сделаем длинную арифметику
};


ObjPtr MakeObj(Obj::Type type);

std::ostream& operator<<(std::ostream& out, const Int& value);

ObjPtr operator/(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator+(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator-(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator*(const ObjPtr& lhs, const ObjPtr& rhs);

const std::unordered_map<std::string, Obj::Type> STRING_TO_TYPE = {
        {"Int", Obj::Type::BASIC_INT},
};