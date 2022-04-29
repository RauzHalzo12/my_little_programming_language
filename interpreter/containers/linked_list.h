#pragma once

#include <cstddef>

template<typename T>
struct Node {
    Node* prev;
    Node* next;
    T value;

    bool HasNext() const {
        return next != nullptr;
    }

    bool HasPrev() const {
        return prev != nullptr;
    }

    void SetNext(const Node<T>& other) {

    }

    void SetPrev(const Node<T>& other) {

    }

    ~Node() {
        prev = nullptr;
        delete next;
    }

};

template<typename T>
class LinkedList {
public:
    LinkedList() = default;

    ~LinkedList() {
        tail_ = nullptr;

        while (front_->HasNext()) {

        }
    }
private:
    std::size_t size_;
    Node<T>* front_;
    Node<T>* tail_;
};