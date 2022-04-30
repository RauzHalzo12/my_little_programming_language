#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>


#include <boost/multiprecision/cpp_int.hpp>

#include "../containers/linked_list.h"

struct Obj;

using ObjPtr = std::shared_ptr<Obj>;

struct Obj {

    enum class Type {
        BASIC_INT,
        BASIC_BOOL,
        BASIC_ITERATOR,
        BASIC_LINKED_LIST,
    };

    explicit Obj(Type t) : type(t) {}
    virtual std::string ToString() const = 0;
    // Арифметика
    virtual bool HasSUMOperator() const = 0;
    virtual bool HasDIVOperator() const = 0;
    virtual bool HasMULOperator() const = 0;
    virtual bool HasSUBOperator() const = 0;

    // Логика
    virtual bool HasLTOperator() const = 0;
    virtual bool HasGTOperator() const = 0;
    virtual bool HasLTOEOperator() const = 0;
    virtual bool HasGTOEOperator() const = 0;

    virtual bool HasEQOperator() const = 0;
    virtual bool HasNEQOperator() const = 0;

    virtual bool HasOROperator() const = 0;
    virtual bool HasANDOperator() const = 0;

    // Контейнерные штуки:
    virtual bool HasGETOperator() const = 0;
    virtual bool HasISVALOperator() const = 0;
    virtual bool HasHSNXTOperator() const = 0;
    virtual bool HasHSPRVOperator() const = 0;
    virtual bool HasINSAOperator() const = 0;
    virtual bool HasINSBOperator() const = 0;
    virtual bool HasERSOperator() const = 0;


    virtual std::size_t Hash() const = 0;
    virtual ~Obj() = default;
    virtual void Assign(ObjPtr other) = 0;

    friend std::ostream& operator<<(std::ostream& out, const ObjPtr& value);

    const Type type;
};

struct ObjectHasher {
    size_t operator()(ObjPtr value) const {
        return value->Hash();
    }
};


class Int : public Obj {
public:
    Int() = default;
    explicit Int(const boost::multiprecision::cpp_int& value) : Obj(Type::BASIC_INT), value_(value) {}
    explicit Int(boost::multiprecision::cpp_int&& value) : Obj(Type::BASIC_INT), value_(value) {}
    explicit Int(const std::string& value) : Obj(Type::BASIC_INT), value_(value) {}

    bool HasSUMOperator() const override;
    bool HasDIVOperator() const override;
    bool HasMULOperator() const override;
    bool HasSUBOperator() const override;

    std::size_t Hash() const override;
    std::string ToString() const override;

    void Assign(ObjPtr other) override;

    bool HasLTOperator()   const override;
    bool HasGTOperator()   const override;
    bool HasLTOEOperator() const override;
    bool HasGTOEOperator() const override;
    bool HasEQOperator()   const override;
    bool HasNEQOperator()  const override;
    bool HasOROperator()   const override;
    bool HasANDOperator()  const override;

    bool HasGETOperator()   const override;
    bool HasISVALOperator() const override;
    bool HasHSNXTOperator() const override;
    bool HasHSPRVOperator() const override;
    bool HasINSAOperator()  const override;
    bool HasINSBOperator()  const override;
    bool HasERSOperator()   const override;


    friend ObjPtr operator+(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator-(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator/(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator*(const ObjPtr& lhs, const ObjPtr& rhs);

    friend ObjPtr operator<(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator<=(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator>(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator>=(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator==(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator!=(const ObjPtr& lhs, const ObjPtr& rhs);

    friend ObjPtr AND(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr OR(const ObjPtr& lhs, const ObjPtr& rhs);

private:
    boost::multiprecision::cpp_int value_;
};

class Bool : public Obj {
public:

    explicit Bool(const std::string& value)
    : Obj(Type::BASIC_BOOL), value_(value == "True" ? true : false) {}

    explicit Bool(bool value) : Obj(Type::BASIC_BOOL), value_(value) {}

    bool HasSUMOperator() const override;
    bool HasDIVOperator() const override;
    bool HasMULOperator() const override;
    bool HasSUBOperator() const override;

    std::size_t Hash() const override;
    std::string ToString() const override;

    void Assign(ObjPtr other) override;

    bool HasLTOperator()   const override;
    bool HasGTOperator()   const override;
    bool HasLTOEOperator() const override;
    bool HasGTOEOperator() const override;
    bool HasEQOperator()   const override;
    bool HasNEQOperator()  const override;
    bool HasOROperator()   const override;
    bool HasANDOperator()  const override;

    bool HasGETOperator()   const override;
    bool HasISVALOperator() const override;
    bool HasHSNXTOperator() const override;
    bool HasHSPRVOperator() const override;
    bool HasINSAOperator()  const override;
    bool HasINSBOperator()  const override;
    bool HasERSOperator()   const override;


    friend ObjPtr operator<(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator<=(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator>(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator>=(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator==(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr operator!=(const ObjPtr& lhs, const ObjPtr& rhs);

    friend ObjPtr AND(const ObjPtr& lhs, const ObjPtr& rhs);
    friend ObjPtr OR(const ObjPtr& lhs, const ObjPtr& rhs);
private:
    bool value_;
};


class Iterator : public Obj {
public:
    enum class State {
        IS_VALID,
        IS_INVALID,
    };

    bool HasSUMOperator() const override;
    bool HasDIVOperator() const override;
    bool HasMULOperator() const override;
    bool HasSUBOperator() const override;

    std::size_t Hash() const override;
    std::string ToString() const override;

    void Assign(ObjPtr other) override;

    bool HasLTOperator()   const override;
    bool HasGTOperator()   const override;
    bool HasLTOEOperator() const override;
    bool HasGTOEOperator() const override;
    bool HasEQOperator()   const override;
    bool HasNEQOperator()  const override;
    bool HasOROperator()   const override;
    bool HasANDOperator()  const override;

    bool HasGETOperator()   const override;
    bool HasISVALOperator() const override;
    bool HasHSNXTOperator() const override;
    bool HasHSPRVOperator() const override;
    bool HasINSAOperator()  const override;
    bool HasINSBOperator()  const override;
    bool HasERSOperator()   const override;

    bicycle::Node<ObjPtr> GetNode() {
        return value;
    }

private:
    bicycle::Node<ObjPtr> value;

};

class LinkedList : public Obj {
public:

    bool HasSUMOperator() const override;
    bool HasDIVOperator() const override;
    bool HasMULOperator() const override;
    bool HasSUBOperator() const override;

    bool HasLTOperator()   const override;
    bool HasGTOperator()   const override;
    bool HasLTOEOperator() const override;
    bool HasGTOEOperator() const override;
    bool HasEQOperator()   const override;
    bool HasNEQOperator()  const override;
    bool HasOROperator()   const override;
    bool HasANDOperator()  const override;

    bool HasGETOperator()   const override;
    bool HasISVALOperator() const override;
    bool HasHSNXTOperator() const override;
    bool HasHSPRVOperator() const override;
    bool HasINSAOperator()  const override;
    bool HasINSBOperator()  const override;
    bool HasERSOperator()   const override;
private:
    bicycle::LinkedList<ObjPtr> list_;
};



ObjPtr MakeObj(Obj::Type type);

std::ostream& operator<<(std::ostream& out, const Int& value);

//////////////////////////////////////////////////////////////////////////////////////////////////////
ObjPtr operator/(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator+(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator-(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator*(const ObjPtr& lhs, const ObjPtr& rhs);

ObjPtr operator<(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator<=(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator>(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator>=(const ObjPtr& lhs, const ObjPtr& rhs);

ObjPtr operator==(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr operator!=(const ObjPtr& lhs, const ObjPtr& rhs);

ObjPtr AND(const ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr OR(const ObjPtr& lhs, const ObjPtr& rhs);


ObjPtr GET(const ObjPtr& lhs);
ObjPtr ISVAL(const ObjPtr& lhs);
ObjPtr HSNXT(const ObjPtr& lhs);
ObjPtr HSPRV(const ObjPtr& lhs);

ObjPtr INSA(ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr INSB(ObjPtr& lhs, const ObjPtr& rhs);
ObjPtr ERS(ObjPtr& lhs, const ObjPtr& rhs);


const std::unordered_map<std::string, Obj::Type> STRING_TO_TYPE = {
        {"Integer",  Obj::Type::BASIC_INT},
        {"Bool", Obj::Type::BASIC_BOOL},
};


