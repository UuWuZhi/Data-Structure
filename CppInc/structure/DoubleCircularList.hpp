#pragma once

#include <iostream>

namespace ds {

template<class T>
class DoubleCircularList {
    struct Node {
        T val;
        Node* prev;
        Node* next;
        explicit Node(const T &value) : val(value), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    size_t count;

public:
    DoubleCircularList() : head(nullptr), count(0) {}

    [[nodiscard]] bool empty() const {
        return count == 0;
    }

    void push_front(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = newNode;
            newNode->prev = newNode->next = newNode;
            ++count;
            return;
        }
        Node* tail = head->prev;
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
        head = newNode;
        ++count;
    }

    void pop_front() const
    {
        if (empty())
        {
            return;
        }
        head->prev->next = head->next;
        head->next->prev = head->prev;
        const Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }

    void push_back(const T& val) {
        if (empty()) {
            push_front(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* tail = head->prev;
        newNode->prev = tail;
        newNode->next = head;
        tail->next = newNode;
        head->prev = newNode;
        ++count;
    }

    void insert(const T& val, const T& pos) {
        if (empty() || pos == 1) {
            push_front(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 1; i < pos - 1; ++i) {
            if (temp->next != head) {
                temp = temp->next;
            }
            else {
                return;
            }
        }
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
        ++count;
    }

    void insert(const T& val) {
        if (empty()) {
            push_front(val);
            return;
        }
        Node* temp = head;
        int pos = 1;
        for (; val > temp->val; ++pos) {
            if (temp->next != head) {
                temp = temp->next;
            }
            else {
                push_back(val);
                return;
            }
        }
        insert(val, pos);
    }

    bool deleteNode(const T& val)
    {
        if (empty()) return false;
        Node* temp = head;
        while (temp->val != val && temp->next != head)
        {
            temp = temp->next;
        }
        if (temp->val != val) return false;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        if (temp == head) head = temp->next;
        delete temp;
        --count;
        return true;
    }

    void deleteAllNodes(const T& val)
    {
        while (deleteNode(val));
    }

    void print() const {
        if (empty()) {
            return;
        }
        Node* temp = head;
        do {
            std::cout << temp->val << " ";
            temp = temp->next;
        } while (temp != head);
        std::cout << std::endl;
    }
};

} // namespace ds
