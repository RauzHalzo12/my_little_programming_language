#pragma once

#include <string>
#include <memory>

struct BasicValue {
    enum class Type {
        BASIC_INT,
        BASIC_STRING,
        CUSTOM_STRUCT,
    };

    BasicValue(Type type) : type(type) {}
    virtual std::string ToString() const = 0;
    virtual size_t Hash() const = 0;

    virtual ~BasicValue() = default;

    const Type type;
};


using ValueHolder = std::shared_ptr<BasicValue>;


struct BasicInt : BasicValue {
    BasicInt(int64_t value = 0) : BasicValue(BasicValue::Type::BASIC_INT), value(value) {}

    std::string ToString() const override {
        return std::to_string(value);
    }

    size_t Hash() const override {
        return std::hash<int64_t>{}(value);
    }

    int64_t value;
};

struct BasicString : BasicValue {
    BasicString(const std::string& value = "") : BasicValue(BasicValue::Type::BASIC_STRING), value(value){}

    std::string ToString() const override {
        return value;
    }

    size_t Hash() const override {
        return std::hash<std::string>{}(value);
    }
    std::string value;
};
