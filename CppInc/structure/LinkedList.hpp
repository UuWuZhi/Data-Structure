#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

namespace ds {

template<class T>
class LinkedList {
    struct Node
    {
        T val;
        Node* next;

        explicit Node(const T &value) : val(value), next(nullptr) {}
    };

    Node* head;
    size_t count;

public:

    LinkedList() : head(new Node(T())), count(0) {}
    LinkedList(const LinkedList& other) : head(new Node(T())), count(0)
    {
        Node* tail = head;
        Node* current = other.head->next;
        while (current != nullptr)
        {
            tail->next = new Node(current->val);
            tail = tail->next;
            current = current->next;
        }
    }

    ~LinkedList()
    {
        clear();
        delete head;
    }

    void clear()
    {
        Node* temp = head->next;
        while (temp != nullptr)
        {
            const Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        head->next = nullptr;
        count = 0;
    }

    void swap(LinkedList& other) noexcept
    {
        std::swap(head, other.head);
        std::swap(count, other.count);
    }

    Node* insert(const T &val, const T &pos) {
        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) {
            if (temp->next != nullptr) {
                temp = temp->next;
            }
            else {
                return nullptr;
            }
        }
        if (temp->next != nullptr) {
            newNode->next = temp->next;
        }
        temp->next = newNode;
        return newNode;
    }

    Node* push_back(const T& val) {
        Node* newNode = new Node(val);
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        return newNode;
    }

    void deleteNode(const T& pos)
    {
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i)
        {
            temp = temp->next;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    LinkedList operator+ (const LinkedList& toMerge) const
    {
        LinkedList result;
        Node* p = this->head->next;
        Node* q = toMerge.head->next;
        Node* tail = result.head;

        while (p != nullptr && q != nullptr)
        {
            if (p->val < q->val)
            {
                tail->next = new Node(p->val);
                p = p->next;
            } else
            {
                tail->next = new Node(q->val);
                q = q->next;
            }
            tail = tail->next;
            ++result.count;
        }
        while (q != nullptr)
        {
            tail->next = new Node(q->val);
            tail = tail->next;
            q = q->next;
            ++result.count;
        }
        while (p != nullptr)
        {
            tail->next = new Node(p->val);
            tail = tail->next;
            p = p->next;
            ++result.count;
        }
        return result;
    }

    LinkedList& operator= (const LinkedList& other)
    {
        if (this == &other) return *this;
        LinkedList temp(other);
        swap(temp);
        return *this;
    }

    void print() {
        Node* temp = head->next;
        while (temp != nullptr) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void printReverse()
    {
        Node* temp = head->next;
        std::stringstream ss;
        while (temp != nullptr)
        {
            ss << temp->val << " ";
            temp = temp->next;
        }
        std::string s = ss.str();
        std::reverse(s.begin(), s.end());
        std::cout << s << std::endl;
    }
};

} // namespace ds
