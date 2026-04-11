#pragma once

#include <iostream>

namespace ds {

template<class T>
class LinkedStack
{
    struct Node
    {
        T data;
        Node* next;
        explicit Node(const T& val, Node* next = nullptr) : data(val), next(next) {}
    };
    Node* top;
    size_t count;
public:
    LinkedStack() : top(nullptr), count(0) {}
    ~LinkedStack()
    {
        clear();
        delete top;
    }
    bool clear()
    {
        if (empty()) return false;
        Node* current = top;
        while (current != nullptr)
        {
            const Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        top->next = nullptr;
        count = 0;
        return true;
    }
    [[nodiscard]] bool empty() const
    {
        return count == 0;
    }
    void push(const T& val)
    {
        Node* newNode = new Node(val, top);
        top = newNode;
        ++count;
    }
    T pop()
    {
        if (empty()) return T{};
        const Node* toDelete = top;
        const T val = toDelete->data;
        top = top->next;
        delete toDelete;
        --count;
        return val;
    }
    T peek()
    {
        if (empty()) return T{};
        return top->data;
    }
    void print()
    {
        if (empty()) return;
        Node* current = top;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    [[nodiscard]] size_t size() const
    {
        return count;
    }
};

} // namespace ds
